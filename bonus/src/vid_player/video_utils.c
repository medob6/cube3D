/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/09/16 15:58:17 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

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
		process_video_packet(vdata, pkt);
	else if (pkt->stream_index == vdata->audio.audio_index)
		process_audio_packet(vdata, pkt);
	return (0);
}
