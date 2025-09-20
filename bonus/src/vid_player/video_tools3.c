/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_tools3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:29 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/20 08:31:07 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

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

void	free_existing_frames(t_vdata *vdata)
{
	if (vdata->video.frame)
		av_frame_free(&vdata->video.frame);
	if (vdata->video.frame_rgb)
		av_frame_free(&vdata->video.frame_rgb);
	if (vdata->audio.frame)
		av_frame_free(&vdata->audio.frame);
}

int	allocate_new_frames(t_vdata *vdata)
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

int	allocate_frame_buffer(t_vdata *vdata)
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

void	setup_frame_arrays(t_vdata *vdata)
{
	av_image_fill_arrays(vdata->video.frame_rgb->data,
		vdata->video.frame_rgb->linesize, vdata->video.buffer, AV_PIX_FMT_BGR24,
		vdata->inf->win_w, vdata->inf->win_h, 1);
}
