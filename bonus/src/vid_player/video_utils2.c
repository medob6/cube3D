/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:32 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/20 08:31:17 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

void	update_audio_timestamp_estimated(t_vdata *vdata, int got)
{
	double	pts_sec;

	pts_sec = vdata->audio.audio_time_written + (double)got
		/ (vdata->audio.codec_ctx->sample_rate * 4);
	vdata->audio.audio_time_written = pts_sec;
}

int	should_queue_audio(t_vdata *vdata)
{
	Uint32	queued;
	Uint32	max_queue;

	queued = SDL_GetQueuedAudioSize(vdata->audio.audio_dev);
	max_queue = calculate_max_queue_size(vdata);
	return (queued < max_queue);
}

void	handle_decoded_audio(t_vdata *vdata, uint8_t *audio_buf, int got)
{
	if (vdata->audio.frame->pts != AV_NOPTS_VALUE)
		update_audio_timestamp_with_pts(vdata);
	else
		update_audio_timestamp_estimated(vdata, got);
	if (should_queue_audio(vdata))
		SDL_QueueAudio(vdata->audio.audio_dev, audio_buf, got);
	vdata->audio.total_audio_bytes_sent += got;
}

Uint32	calculate_max_queue_size(t_vdata *vdata)
{
	int		bytes_per_sample;
	int		channels;
	int		sample_rate;
	Uint32	max_queue;

	bytes_per_sample
		= av_get_bytes_per_sample(vdata->audio.codec_ctx->sample_fmt);
	channels = vdata->audio.codec_ctx->ch_layout.nb_channels;
	sample_rate = vdata->audio.codec_ctx->sample_rate;
	max_queue = (Uint32)(290 * sample_rate * bytes_per_sample * channels);
	return (max_queue);
}

int	initialize_player_data(t_vdata **vdata, char *path)
{
	*vdata = malloc(sizeof(t_vdata));
	if (!*vdata)
		return (-1);
	memset(*vdata, 0, sizeof(t_vdata));
	(*vdata)->inf = get_game();
	(*vdata)->video_path = path;
	if (initialize_video_player(*vdata) < 0)
	{
		cleanup_video_player(*vdata);
		free(*vdata);
		*vdata = NULL;
		return (-1);
	}
	return (0);
}
