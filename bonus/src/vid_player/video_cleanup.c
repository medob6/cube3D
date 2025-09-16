/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/09/16 16:19:53 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

void	cleanup_video_resources(t_vdata *vdata)
{
	if (vdata->video.sws_ctx)
		sws_freeContext(vdata->video.sws_ctx);
	if (vdata->video.buffer)
		av_free(vdata->video.buffer);
	if (vdata->video.frame)
		av_frame_free(&vdata->video.frame);
	if (vdata->video.frame_rgb)
		av_frame_free(&vdata->video.frame_rgb);
	if (vdata->video.codec_ctx)
		avcodec_free_context(&vdata->video.codec_ctx);
	if (vdata->video.fmt_ctx)
		avformat_close_input(&vdata->video.fmt_ctx);
}

void	cleanup_audio_resources(t_vdata *vdata)
{
	if (vdata->audio.frame)
		av_frame_free(&vdata->audio.frame);
	if (vdata->audio.codec_ctx)
		avcodec_free_context(&vdata->audio.codec_ctx);
	if (vdata->audio.swr_ctx)
		swr_free(&vdata->audio.swr_ctx);
	if (vdata->audio.audio_dev)
		SDL_CloseAudioDevice(vdata->audio.audio_dev);
}

void	cleanup_mlx_resources(t_vdata *vdata)
{
	if (vdata->image.img && vdata->inf->mlx)
		mlx_destroy_image(vdata->inf->mlx, vdata->image.img);
}

void	cleanup_video_player(t_vdata *vdata)
{
	cleanup_video_resources(vdata);
	cleanup_audio_resources(vdata);
	cleanup_mlx_resources(vdata);
	if (vdata->video.codec_ctx)
		avcodec_close(vdata->video.codec_ctx);
	SDL_Quit();
	avformat_network_deinit();
}
