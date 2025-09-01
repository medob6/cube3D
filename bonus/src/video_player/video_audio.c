// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   video_audio.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
// /*   Updated: 2025/07/31 10:05:24 by mbousset         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "video_bs.h"

// static int	open_audio_device(t_vdata *vdata, SDL_AudioSpec *wanted_spec,
// 		SDL_AudioSpec *obtained_spec)
// {
// 	wanted_spec->freq = vdata->audio.codec_ctx->sample_rate;
// 	wanted_spec->format = AUDIO_S16SYS;
// 	wanted_spec->channels = 2;
// 	wanted_spec->silence = 0;
// 	wanted_spec->samples = 1024;
// 	wanted_spec->callback = NULL;
// 	wanted_spec->userdata = vdata->audio.codec_ctx;
// 	vdata->audio.audio_dev = SDL_OpenAudioDevice(NULL, 0, wanted_spec,
// 			obtained_spec, 0);
// 	if (!vdata->audio.audio_dev)
// 		return (-1);
// 	SDL_PauseAudioDevice(vdata->audio.audio_dev, 0);
// 	return (0);
// }

// static int	setup_swr_context(t_vdata *vdata)
// {
// 	vdata->audio.swr_ctx = swr_alloc();
// 	if (!vdata->audio.swr_ctx)
// 		return (-1);
// 	av_opt_set_chlayout(vdata->audio.swr_ctx, "in_chlayout",
// 		&vdata->audio.codec_ctx->ch_layout, 0);
// 	av_opt_set_chlayout(vdata->audio.swr_ctx, "out_chlayout",
// 		&(AVChannelLayout)AV_CHANNEL_LAYOUT_STEREO, 0);
// 	av_opt_set_int(vdata->audio.swr_ctx, "in_sample_rate",
// 		vdata->audio.codec_ctx->sample_rate, 0);
// 	av_opt_set_int(vdata->audio.swr_ctx, "out_sample_rate",
// 		vdata->audio.codec_ctx->sample_rate, 0);
// 	return (0);
// }

// static int	configure_swr_formats(t_vdata *vdata)
// {
// 	av_opt_set_sample_fmt(vdata->audio.swr_ctx, "in_sample_fmt",
// 		vdata->audio.codec_ctx->sample_fmt, 0);
// 	av_opt_set_sample_fmt(vdata->audio.swr_ctx, "out_sample_fmt",
// 		AV_SAMPLE_FMT_S16, 0);
// 	if (swr_init(vdata->audio.swr_ctx) < 0)
// 		return (-1);
// 	return (0);
// }

// int	setup_audio_device(t_vdata *vdata)
// {
// 	SDL_AudioSpec	wanted_spec;
// 	SDL_AudioSpec	obtained_spec;

// 	if (vdata->audio.audio_index == -1)
// 		return (0);
// 	if (open_audio_device(vdata, &wanted_spec, &obtained_spec) < 0)
// 		return (-1);
// 	if (setup_swr_context(vdata) < 0)
// 		return (-1);
// 	if (configure_swr_formats(vdata) < 0)
// 		return (-1);
// 	return (0);
// }
