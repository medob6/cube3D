/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/07/28 09:26:31 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"

int	create_color(uint8_t *src, int x)
{
	int	b;
	int	g;
	int	r;
	int	color;

	b = src[x * 3 + 0];
	g = src[x * 3 + 1];
	r = src[x * 3 + 2];
	color = (r << 16) | (g << 8) | b;
	return (color);
}

t_audio_convert	init_audio_convert(t_audio_decode *decode)
{
	t_audio_convert	conv;

	conv.ctx = decode->ctx;
	conv.frame = decode->frame;
	conv.out_buf = decode->out_buf;
	conv.out_buf_size = decode->out_buf_size;
	conv.swr_ctx = decode->swr_ctx;
	return (conv);
}

double	calculate_seconds_queued(t_vdata *vdata, Uint32 bytes_queued)
{
	int	bytes_per_sample;
	int	channels;
	int	sample_rate;

	bytes_per_sample = av_get_bytes_per_sample(vdata->audio.codec_ctx->sample_fmt);
	channels = vdata->audio.codec_ctx->ch_layout.nb_channels;
	sample_rate = vdata->audio.codec_ctx->sample_rate;
	return ((double)bytes_queued / (sample_rate * bytes_per_sample * channels));
}

int	decode_audio_frame_wrapper(t_vdata *vdata, AVPacket *pkt,
		t_audio_process *proc)
{
	t_audio_decode	decode;

	decode.ctx = vdata->audio.codec_ctx;
	decode.pkt = pkt;
	decode.frame = vdata->audio.frame;
	decode.out_buf = proc->audio_buf;
	decode.out_buf_size = proc->out_size;
	decode.swr_ctx = vdata->audio.swr_ctx;
	return (decode_audio_frame(&decode));
}

static void	update_audio_timestamp_with_pts(t_vdata *vdata)
{
	double	pts_sec;

	if (vdata->audio.frame->pts != AV_NOPTS_VALUE)
	{
		pts_sec = vdata->audio.frame->pts * av_q2d(vdata->audio.time_base);
		vdata->audio.audio_time_written = pts_sec;
	}
	else
	{
		pts_sec = vdata->audio.audio_time_written;
		vdata->audio.audio_time_written = pts_sec;
	}
}

static void	update_audio_timestamp_estimated(t_vdata *vdata, int got)
{
	double	pts_sec;

	pts_sec = vdata->audio.audio_time_written + (double)got
		/ (vdata->audio.codec_ctx->sample_rate * 4);
	vdata->audio.audio_time_written = pts_sec;
}

static int	should_queue_audio(t_vdata *vdata)
{
	Uint32	queued;
	Uint32	max_queue;

	queued = SDL_GetQueuedAudioSize(vdata->audio.audio_dev);
	max_queue = calculate_max_queue_size(vdata);
	return (queued < max_queue);
}

void	handle_decoded_audio(t_vdata *vdata, uint8_t *audio_buf, int got)
{
	if (vdata->audio.frame->pts != AV_NOPTS_VALUE)
		update_audio_timestamp_with_pts(vdata);
	else
		update_audio_timestamp_estimated(vdata, got);

	if (should_queue_audio(vdata))
		SDL_QueueAudio(vdata->audio.audio_dev, audio_buf, got);
	vdata->audio.total_audio_bytes_sent += got; 
}


Uint32	calculate_max_queue_size(t_vdata *vdata)
{
	int		bytes_per_sample;
	int		channels;
	int		sample_rate;
	Uint32	max_queue;

	bytes_per_sample = av_get_bytes_per_sample(vdata->audio.codec_ctx->sample_fmt);
	channels = vdata->audio.codec_ctx->ch_layout.nb_channels;
	sample_rate = vdata->audio.codec_ctx->sample_rate;
	max_queue = (Uint32)(290 * sample_rate * bytes_per_sample * channels);
	return (max_queue);
}

int	initialize_player_data(t_vdata **vdata, char *path)
{
	*vdata = malloc(sizeof(t_vdata));
	if (!*vdata)
		return (-1);
	memset(*vdata, 0, sizeof(t_vdata));
	(*vdata)->inf = get_game();
	(*vdata)->video_path = path;
	if (initialize_video_player(*vdata) < 0)
	{
		cleanup_video_player(*vdata);
		free(*vdata);
		*vdata = NULL;
		return (-1);
	}
	return (0);
}

int	handle_video_end(t_vdata **vdata, int *video_initialized)
{
	cleanup_video_player(*vdata);
	free(*vdata);
	*vdata = NULL;
	*video_initialized = 0;
	return (1);
}

int	process_packet_by_type(t_vdata *vdata, AVPacket *pkt)
{
	if (pkt->stream_index == vdata->video.video_index)
	{
		process_video_packet(vdata, pkt);
		// printf("1\n");
	}
	else if (pkt->stream_index == vdata->audio.audio_index)
	{
		process_audio_packet(vdata, pkt);
		// printf("2\n");
	}
	return (0);
}
