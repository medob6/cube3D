/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:06 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/16 16:13:07 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

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

	bytes_per_sample
		= av_get_bytes_per_sample(vdata->audio.codec_ctx->sample_fmt);
	channels = vdata->audio.codec_ctx->ch_layout.nb_channels;
	sample_rate = vdata->audio.codec_ctx->sample_rate;
	if (bytes_per_sample <= 0 || channels <= 0 || sample_rate <= 0)
		return (0.0);
	queued_bytes = SDL_GetQueuedAudioSize(vdata->audio.audio_dev);
	played_bytes = vdata->audio.total_audio_bytes_sent - queued_bytes;
	return ((double)played_bytes / (bytes_per_sample * channels * sample_rate));
}

enum AVPixelFormat	normalize_pix_fmt(enum AVPixelFormat fmt,
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

int	initialize_sws_context(t_vdata *vdata)
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

void	scale_video_frame(t_vdata *vdata)
{
	sws_scale(vdata->video.sws_ctx,
		(const uint8_t * const *)vdata->video.frame->data,
		vdata->video.frame->linesize, 0, vdata->video.frame->height,
		vdata->video.frame_rgb->data, vdata->video.frame_rgb->linesize);
}
