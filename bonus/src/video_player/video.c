/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:03:45 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/13 12:15:15 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

int	find_stream_index(AVFormatContext *fmt_ctx, enum AVMediaType type)
{
	unsigned int	i;

	i = 0;
	while (i < fmt_ctx->nb_streams)
	{
		if (fmt_ctx->streams[i]->codecpar->codec_type == type)
			return (i);
		i++;
	}
	return (-1);
}

static void	process_pixel_row(t_image *img, AVFrame *frame_rgb, int y)
{
	uint8_t	*src;
	char	*dst;
	int		x;

	src = frame_rgb->data[0] + y * frame_rgb->linesize[0];
	dst = img->addr + y * img->line_len;
	x = 0;
	while (x < img->w)
	{
		((unsigned int *)dst)[x] = create_color(src, x);
		x++;
	}
}

void	draw_frame_to_mlx(t_image *img, AVFrame *frame_rgb)
{
	int	y;

	y = 0;
	while (y < img->h)
	{
		process_pixel_row(img, frame_rgb, y);
		y++;
	}
}

static int	send_packet_to_decoder(AVCodecContext *ctx, AVPacket *pkt)
{
	int	ret;

	ret = avcodec_send_packet(ctx, pkt);
	if (ret < 0)
		return (0);
	return (1);
}

static int	convert_audio_frame(t_audio_convert *conv)
{
	int	len2;
	int	data_size;

	len2 = swr_convert(conv->swr_ctx, &conv->out_buf, conv->out_buf_size / 2,
			(const uint8_t **)conv->frame->data, conv->frame->nb_samples);
	data_size = len2 * 2 * 2;
	return (data_size);
}

int	decode_audio_frame(t_audio_decode *decode)
{
	t_audio_convert	conv;
	int				data_size;

	data_size = 0;
	if (!send_packet_to_decoder(decode->ctx, decode->pkt))
		return (0);
	if (avcodec_receive_frame(decode->ctx, decode->frame) == 0)
	{
		conv = init_audio_convert(decode);
		data_size = convert_audio_frame(&conv);
	}
	return (data_size);
}

double	get_audio_clock(t_vdata *vdata)
{
	int		bytes_per_sample;
	int		channels;
	int		sample_rate;
	Uint32	queued_bytes;
	Uint64	played_bytes;
	double	seconds_played;

	bytes_per_sample = av_get_bytes_per_sample(vdata->audio.codec_ctx->sample_fmt);
	channels = vdata->audio.codec_ctx->ch_layout.nb_channels;
	sample_rate = vdata->audio.codec_ctx->sample_rate;
	if (bytes_per_sample <= 0 || channels <= 0 || sample_rate <= 0)
		return (0.0);
	queued_bytes = SDL_GetQueuedAudioSize(vdata->audio.audio_dev);
	played_bytes = vdata->audio.total_audio_bytes_sent - queued_bytes;
	seconds_played = (double)played_bytes / (bytes_per_sample * channels
			* sample_rate);
	return (seconds_played);
}

static enum AVPixelFormat	normalize_pix_fmt(enum AVPixelFormat fmt,
		int *range)
{
	if (fmt == AV_PIX_FMT_YUVJ420P)
	{
		*range = AVCOL_RANGE_JPEG;
		return (AV_PIX_FMT_YUV420P);
	}
	if (fmt == AV_PIX_FMT_YUVJ422P)
	{
		*range = AVCOL_RANGE_JPEG;
		return (AV_PIX_FMT_YUV422P);
	}
	if (fmt == AV_PIX_FMT_YUVJ444P)
	{
		*range = AVCOL_RANGE_JPEG;
		return (AV_PIX_FMT_YUV444P);
	}
	if (fmt == AV_PIX_FMT_YUVJ440P)
	{
		*range = AVCOL_RANGE_JPEG;
		return (AV_PIX_FMT_YUV440P);
	}
	*range = AVCOL_RANGE_MPEG;
	return (fmt);
}

static int	initialize_sws_context(t_vdata *vdata)
{
	enum AVPixelFormat	src_pix_fmt;
	int					range;

	if (!vdata->video.sws_ctx)
	{
		src_pix_fmt = normalize_pix_fmt(vdata->video.frame->format, &range);
		vdata->video.frame->color_range = range;
		vdata->video.sws_ctx = sws_getContext(vdata->video.frame->width,
				vdata->video.frame->height, src_pix_fmt, vdata->inf->win_w,
				vdata->inf->win_h, AV_PIX_FMT_BGR24, SWS_BILINEAR, NULL, NULL,
				NULL);
	}
	return (vdata->video.sws_ctx != NULL);
}

static void	scale_video_frame(t_vdata *vdata)
{
	sws_scale(vdata->video.sws_ctx,
		(const uint8_t *const *)vdata->video.frame->data,
		vdata->video.frame->linesize, 0, vdata->video.frame->height,
		vdata->video.frame_rgb->data, vdata->video.frame_rgb->linesize);
}

void	handle_video_sync(t_vdata *vdata, double video_pts_sec)
{
	double	audio_clock;
	double	diff;

	audio_clock = get_audio_clock(vdata);
	diff = video_pts_sec - audio_clock;
	if (diff > 0.040)
	{
		if (diff > 1.0)
		{
			diff = 1.0;
		}
		usleep(diff * 10000);
	}
}

static void	display_video_frame(t_vdata *vdata)
{
	draw_frame_to_mlx(&vdata->image, vdata->video.frame_rgb);
	mlx_put_image_to_window(vdata->inf->mlx, vdata->inf->win, vdata->image.img,
		0, 0);
}

static void	process_frame_with_pts(t_vdata *vdata)
{
	double	video_pts_sec;

	if (vdata->video.frame->pts != AV_NOPTS_VALUE && 0)
	{
		video_pts_sec = vdata->video.frame->pts
			* av_q2d(vdata->video.time_base);
		handle_video_sync(vdata, video_pts_sec);
		display_video_frame(vdata);
	}
	else
	{
		SDL_Delay(25);
		display_video_frame(vdata);
	}
}

static int	process_decoded_video_frame(t_vdata *vdata)
{
	// enum AVPixelFormat	src_pix_fmt;
	if (!initialize_sws_context(vdata))
		return (-1);
	// src_pix_fmt = vdata->video.frame->format;
	scale_video_frame(vdata);
	process_frame_with_pts(vdata);
	return (0);
}

int	process_video_packet(t_vdata *vdata, AVPacket *pkt)
{
	int	ret;

	ret = avcodec_send_packet(vdata->video.codec_ctx, pkt);
	if (ret < 0)
		return (ret);
	ret = avcodec_receive_frame(vdata->video.codec_ctx, vdata->video.frame);
	while (ret == 0)
	{
		if (process_decoded_video_frame(vdata) < 0)
			return (-1);
		ret = avcodec_receive_frame(vdata->video.codec_ctx, vdata->video.frame);
	}
	return (0);
}

int	process_audio_packet(t_vdata *vdata, AVPacket *pkt)
{
	t_audio_process	proc;
	int				got;

	proc.out_size = sizeof(proc.audio_buf);
	if (vdata->audio.audio_index == -1)
		return (0);
	got = decode_audio_frame_wrapper(vdata, pkt, &proc);
	if (got > 0)
		handle_decoded_audio(vdata, proc.audio_buf, got);
	return (0);
}

static void	free_existing_frames(t_vdata *vdata)
{
	if (vdata->video.frame)
		av_frame_free(&vdata->video.frame);
	if (vdata->video.frame_rgb)
		av_frame_free(&vdata->video.frame_rgb);
	if (vdata->audio.frame)
		av_frame_free(&vdata->audio.frame);
}

static int	allocate_new_frames(t_vdata *vdata)
{
	vdata->video.frame = av_frame_alloc();
	vdata->video.frame_rgb = av_frame_alloc();
	vdata->audio.frame = av_frame_alloc();
	if (!vdata->video.frame || !vdata->video.frame_rgb || !vdata->audio.frame)
	{
		free_existing_frames(vdata);
		return (-1);
	}
	return (0);
}

static int	allocate_frame_buffer(t_vdata *vdata)
{
	int	num_bytes;

	num_bytes = av_image_get_buffer_size(AV_PIX_FMT_BGR24, vdata->inf->win_w,
			vdata->inf->win_h, 1);
	if (vdata->video.buffer)
		av_free(vdata->video.buffer);
	vdata->video.buffer = av_malloc(num_bytes);
	if (!vdata->video.buffer)
	{
		cleanup_video_player(vdata);
		return (-1);
	}
	return (0);
}

static void	setup_frame_arrays(t_vdata *vdata)
{
	av_image_fill_arrays(vdata->video.frame_rgb->data,
		vdata->video.frame_rgb->linesize, vdata->video.buffer, AV_PIX_FMT_BGR24,
		vdata->inf->win_w, vdata->inf->win_h, 1);
}

int	allocate_video_frames(t_vdata *vdata)
{
	free_existing_frames(vdata);
	if (allocate_new_frames(vdata) < 0)
		return (-1);
	if (allocate_frame_buffer(vdata) < 0)
		return (-1);
	setup_frame_arrays(vdata);
	return (0);
}

int	create_mlx_image(t_vdata *vdata)
{
	vdata->image.w = vdata->inf->win_w;
	vdata->image.h = vdata->inf->win_h;
	vdata->image.img = mlx_new_image(vdata->inf->mlx, vdata->image.w,
			vdata->image.h);
	vdata->image.addr = mlx_get_data_addr(vdata->image.img, &vdata->image.bpp,
			&vdata->image.line_len, &vdata->image.endian);
	if (!vdata->image.img || !vdata->image.addr)
		return (-1);
	return (0);
}

int	play_video(char *path)
{
	AVPacket		pkt;
	static int		video_initialized = 0;
	static t_vdata	*vdata = NULL;

	if (!video_initialized)
	{
		if (initialize_player_data(&vdata, path) < 0)
			return (-1);
		// av_dump_format(vdata->video.fmt_ctx, 0, vdata->video_path, 0);
		video_initialized = 1;
	}
	if (av_read_frame(vdata->video.fmt_ctx, &pkt) < 0)
		return (handle_video_end(&vdata, &video_initialized));
	// while (true)
	// {
	process_packet_by_type(vdata, &pkt);
	av_packet_unref(&pkt);
	// }
	return (0);
}
