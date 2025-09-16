/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:10 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/16 16:13:11 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

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

void	display_video_frame(t_vdata *vdata)
{
	draw_frame_to_mlx(&vdata->image, vdata->video.frame_rgb);
	mlx_put_image_to_window(vdata->inf->mlx, vdata->inf->win, vdata->image.img,
		0, 0);
}

void	process_frame_with_pts(t_vdata *vdata)
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

int	process_decoded_video_frame(t_vdata *vdata)
{
	if (!initialize_sws_context(vdata))
		return (-1);
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
