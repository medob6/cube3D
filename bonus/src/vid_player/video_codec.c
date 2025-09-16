/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_codec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/09/16 16:11:43 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

int	setup_audio_codec(t_vdata *vdata)
{
	AVCodecParameters	*codec_par;

	if (vdata->audio.audio_index == -1)
		return (0);
	codec_par
		= vdata->video.fmt_ctx->streams[vdata->audio.audio_index]->codecpar;
	if (find_and_allocate_audio_codec(vdata, codec_par) < 0)
		return (-1);
	if (configure_audio_codec(vdata, codec_par) < 0)
		return (-1);
	vdata->audio.time_base
		= vdata->video.fmt_ctx->streams[vdata->audio.audio_index]->time_base;
	if (allocate_audio_frame(vdata) < 0)
		return (-1);
	return (0);
}

int	init_format_context(const char *url, AVFormatContext **fmt_ctx)
{
	avformat_network_init();
	if (avformat_open_input(fmt_ctx, url, NULL, NULL) != 0)
		return (-1);
	if (avformat_find_stream_info(*fmt_ctx, NULL) < 0)
	{
		avformat_close_input(fmt_ctx);
		return (-1);
	}
	return (0);
}

static int	find_stream_indices(t_vdata *vdata)
{
	vdata->audio.audio_index = find_stream_index(vdata->video.fmt_ctx,
			AVMEDIA_TYPE_AUDIO);
	vdata->video.video_index = find_stream_index(vdata->video.fmt_ctx,
			AVMEDIA_TYPE_VIDEO);
	if (vdata->video.video_index == -1)
		return (-1);
	return (0);
}

static int	setup_codecs_and_frames(t_vdata *vdata)
{
	if (setup_video_codec(vdata) < 0)
		return (-1);
	if (setup_audio_codec(vdata) < 0)
		return (-1);
	if (allocate_video_frames(vdata) < 0)
		return (-1);
	return (0);
}

int	initialize_video_player(t_vdata *vdata)
{
	vdata->video.fmt_ctx = NULL;
	if (init_format_context(vdata->video_path, &vdata->video.fmt_ctx) < 0)
		return (-1);
	if (find_stream_indices(vdata) < 0)
		return (-1);
	if (setup_codecs_and_frames(vdata) < 0)
		return (-1);
	if (create_mlx_image(vdata) < 0)
		return (-1);
	if (setup_audio_device(vdata) < 0)
		return (-1);
	return (0);
}
