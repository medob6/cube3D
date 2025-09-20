/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:23 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/20 08:31:14 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

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

	bytes_per_sample
		= av_get_bytes_per_sample(vdata->audio.codec_ctx->sample_fmt);
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

void	update_audio_timestamp_with_pts(t_vdata *vdata)
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
