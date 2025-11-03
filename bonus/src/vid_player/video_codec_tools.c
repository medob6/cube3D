/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_codec_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:12:34 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/20 08:30:44 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

int	find_and_allocate_video_codec(t_vdata *vdata,
		AVCodecParameters *codecPar)
{
	vdata->video.codec
		= avcodec_find_decoder(codecPar->codec_id);
	if (!vdata->video.codec)
		return (-1);
	vdata->video.codec_ctx
		= avcodec_alloc_context3(vdata->video.codec);
	if (!vdata->video.codec_ctx)
		return (-1);
	return (0);
}

int	configure_video_codec(t_vdata *vdata, AVCodecParameters *codecPar)
{
	if (avcodec_parameters_to_context(vdata->video.codec_ctx, codecPar) < 0)
		return (-1);
	if (avcodec_open2(vdata->video.codec_ctx, vdata->video.codec, NULL) < 0)
		return (-1);
	return (0);
}

int	setup_video_codec(t_vdata *vdata)
{
	AVCodecParameters	*codec_par;

	codec_par
		= vdata->video.fmt_ctx->streams[vdata->video.video_index]->codecpar;
	if (find_and_allocate_video_codec(vdata, codec_par) < 0)
		return (-1);
	if (configure_video_codec(vdata, codec_par) < 0)
		return (-1);
	vdata->video.time_base
		= vdata->video.fmt_ctx->streams[vdata->video.video_index]->time_base;
	return (0);
}

int	find_and_allocate_audio_codec(t_vdata *vdata,
		AVCodecParameters *codecPar)
{
	vdata->audio.codec
		= avcodec_find_decoder(codecPar->codec_id);
	if (!vdata->audio.codec)
		return (-1);
	vdata->audio.codec_ctx
		= avcodec_alloc_context3(vdata->audio.codec);
	if (!vdata->audio.codec_ctx)
		return (-1);
	return (0);
}

int	configure_audio_codec(t_vdata *vdata, AVCodecParameters *codecPar)
{
	if (avcodec_parameters_to_context(vdata->audio.codec_ctx, codecPar) < 0)
		return (-1);
	if (avcodec_open2(vdata->audio.codec_ctx, vdata->audio.codec, NULL) < 0)
		return (-1);
	return (0);
}
