/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_codec_tools1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:11:53 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/20 08:30:50 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

int	allocate_audio_frame(t_vdata *vdata)
{
	if (!vdata->audio.frame)
	{
		vdata->audio.frame = av_frame_alloc();
		if (!vdata->audio.frame)
			return (-1);
	}
	return (0);
}
