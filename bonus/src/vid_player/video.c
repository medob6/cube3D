/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:03:45 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 16:05:27 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

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
		video_initialized = 1;
	}
	if (av_read_frame(vdata->video.fmt_ctx, &pkt) < 0)
		return (handle_video_end(&vdata, &video_initialized));
	process_packet_by_type(vdata, &pkt);
	av_packet_unref(&pkt);
	return (0);
}

bool	handle_video(char *path, t_video *vid)
{
	if (vid->played)
		return (false);
	if (!vid->active)
	{
		vid->active = true;
		vid->result = 0;
	}
	vid->result = play_video(path);
	if (vid->result == 0)
		return (true);
	else if (vid->result == 1)
	{
		vid->active = false;
		vid->played = true;
		return (false);
	}
	else if (vid->result == -1)
	{
		usleep(3000);
		printf("Error: err while processing video\n");
		vid->active = false;
		vid->played = true;
		return (false);
	}
	return (false);
}
