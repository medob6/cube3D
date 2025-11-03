/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:13 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/20 08:30:58 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video_bs.h"

int	find_stream_index(AVFormatContext *fmt_ctx, enum AVMediaType type)
{
	unsigned int	i;

	i = 0;
	while (i < fmt_ctx->nb_streams)
	{
		if (fmt_ctx->streams[i]->codecpar->codec_type == type)
			return (i);
		i++;
	}
	return (-1);
}

void	process_pixel_row(t_image *img, AVFrame *frame_rgb, int y)
{
	uint8_t	*src;
	char	*dst;
	int		x;

	src = frame_rgb->data[0] + y * frame_rgb->linesize[0];
	dst = img->addr + y * img->line_len;
	x = 0;
	while (x < img->w)
	{
		((unsigned int *)dst)[x] = create_color(src, x);
		x++;
	}
}

void	draw_frame_to_mlx(t_image *img, AVFrame *frame_rgb)
{
	int	y;

	y = 0;
	while (y < img->h)
	{
		process_pixel_row(img, frame_rgb, y);
		y++;
	}
}

int	send_packet_to_decoder(AVCodecContext *ctx, AVPacket *pkt)
{
	int	ret;

	ret = avcodec_send_packet(ctx, pkt);
	if (ret < 0)
		return (0);
	return (1);
}

int	convert_audio_frame(t_audio_convert *conv)
{
	int	len2;
	int	data_size;

	len2 = swr_convert(conv->swr_ctx, &conv->out_buf, conv->out_buf_size / 2,
			(const uint8_t **)conv->frame->data, conv->frame->nb_samples);
	data_size = len2 * 2 * 2;
	return (data_size);
}
