#include "video.h"

int	find_stream_index(AVFormatContext *fmt_ctx, enum AVMediaType type)
{
	for (unsigned int i = 0; i < fmt_ctx->nb_streams; i++)
	{
		if (fmt_ctx->streams[i]->codecpar->codec_type == type)
			return (i);
	}
	return (-1);
}

void	draw_frame_to_mlx(t_image *img, AVFrame *frame_rgb)
{
	uint8_t	*src;
	char	*dst;
	int		r;
	int		g;
	int		b;
	int		color;

	int x, y;
	for (y = 0; y < img->h; y++)
	{
		src = frame_rgb->data[0] + y * frame_rgb->linesize[0];
		dst = img->addr + y * img->line_len;
		for (x = 0; x < img->w; x++)
		{
			r = src[x * 3 + 0];
			g = src[x * 3 + 1];
			b = src[x * 3 + 2];
			color = (r << 16) | (g << 8) | b;
			((unsigned int *)dst)[x] = color;
		}
	}
}

int	decode_audio_frame(AVCodecContext *aCodecCtx, AVPacket *pkt, AVFrame *frame,
		uint8_t *out_buf, int out_buf_size, struct SwrContext *swr_ctx)
{
	int	dst_nb_samples;

	int ret, len2, data_size = 0;
	ret = avcodec_send_packet(aCodecCtx, pkt);
	if (ret < 0)
		return (0);
	if (avcodec_receive_frame(aCodecCtx, frame) == 0)
	{
		dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx,
					aCodecCtx->sample_rate) + frame->nb_samples,
				aCodecCtx->sample_rate, aCodecCtx->sample_rate, AV_ROUND_UP);
		len2 = swr_convert(swr_ctx, &out_buf, out_buf_size / 2,
				(const uint8_t **)frame->data, frame->nb_samples);
		data_size = len2 * 2 * 2;
	}
	return (data_size);
}

// Audio clock in seconds
double	get_audio_clock(t_vdata *vdata)
{
	Uint32	bytes_queued;
	int		bytes_per_sample;
	int		channels;
	double	seconds_queued;

	if (!vdata->audio.audio_dev || vdata->audio.audio_index == -1)
		return (0.0);
	bytes_queued = SDL_GetQueuedAudioSize(vdata->audio.audio_dev);
	bytes_per_sample = av_get_bytes_per_sample(vdata->audio.codec_ctx->sample_fmt);
	channels = vdata->audio.codec_ctx->ch_layout.nb_channels;
	if (bytes_per_sample <= 0 || channels <= 0
		|| vdata->audio.codec_ctx->sample_rate <= 0)
		return (vdata->audio.audio_time_written);
	seconds_queued = (double)bytes_queued / (vdata->audio.codec_ctx->sample_rate
			* bytes_per_sample * channels);
	return (vdata->audio.audio_time_written - seconds_queued);
}

int	process_video_packet(t_vdata *vdata, AVPacket *pkt)
{
	int	ret;

	double video_pts_sec, audio_clock, diff;
	ret = avcodec_send_packet(vdata->video.codec_ctx, pkt);
	if (ret < 0)
		return (ret);
	while ((ret = avcodec_receive_frame(vdata->video.codec_ctx,
				vdata->video.frame)) == 0)
	{
		if (!vdata->video.sws_ctx)
		{
			vdata->video.sws_ctx = sws_getContext(vdata->video.frame->width,
					vdata->video.frame->height, vdata->video.frame->format,
					vdata->inf->win_w, vdata->inf->win_h, AV_PIX_FMT_RGB24,
					SWS_LANCZOS, NULL, NULL, NULL);
		}
		if (vdata->video.sws_ctx)
		{
			sws_scale(vdata->video.sws_ctx,
				(const uint8_t *const *)vdata->video.frame->data,
				vdata->video.frame->linesize, 0, vdata->video.frame->height,
				vdata->video.frame_rgb->data, vdata->video.frame_rgb->linesize);
			// --- Sync with audio ---
			if (vdata->video.frame->pts != AV_NOPTS_VALUE)
			{
				video_pts_sec = vdata->video.frame->pts
					* av_q2d(vdata->video.time_base);
				// printf("Video PTS: %f\n", video_pts_sec);
				audio_clock = get_audio_clock(vdata);
				diff = video_pts_sec - audio_clock;
				// If video is ahead of audio, delay
				if (diff > 0.040) // 40ms threshold for delay
				{
					// Cap the delay to prevent excessive waiting
					if (diff > 1.0)
						diff = 1.0;
					usleep(diff * 10000); // Convert to microseconds
				}
				// If video is significantly behind audio, skip frame
				// else if (diff < -0.100) // 100ms threshold for skip
				// {
				// 	continue ;
				// }
				// Display the frame (sync is close enough or acceptable)
				draw_frame_to_mlx(&vdata->image, vdata->video.frame_rgb);
				mlx_put_image_to_window(vdata->inf->mlx, vdata->inf->win,
					vdata->image.img, 0, 0);
			}
			else
			{
				// No PTS available, just display the frame
				usleep(30000); // Small delay to allow for rendering
				draw_frame_to_mlx(&vdata->image, vdata->video.frame_rgb);
				mlx_put_image_to_window(vdata->inf->mlx, vdata->inf->win,
					vdata->image.img, 0, 0);
			}
		}
	}
	return (0);
}

int	process_audio_packet(t_vdata *vdata, AVPacket *pkt)
{
	uint8_t	audio_buf[192000 * 3 / 2];
	int		out_size;
	int		got;
	double	pts_sec;
	Uint32	queued;
	int		bytes_per_sample;
	int		channels;
	int		sample_rate;

	out_size = sizeof(audio_buf);
	if (vdata->audio.audio_index == -1)
		return (0);
	got = decode_audio_frame(vdata->audio.codec_ctx, pkt, vdata->audio.frame,
			audio_buf, out_size, vdata->audio.swr_ctx);
	if (got > 0)
	{
		// Update audio timestamp
		if (vdata->audio.frame->pts != AV_NOPTS_VALUE)
		{
			pts_sec = vdata->audio.frame->pts * av_q2d(vdata->audio.time_base);
			vdata->audio.audio_time_written = pts_sec;
		}
		else
		{
			// Estimate timestamp based on samples
			pts_sec = vdata->audio.audio_time_written + (double)got
				/ (vdata->audio.codec_ctx->sample_rate * 4);
			vdata->audio.audio_time_written = pts_sec;
		}
		// Simple queue management to prevent overflow
		queued = SDL_GetQueuedAudioSize(vdata->audio.audio_dev);
		// Dynamically limit queue size to about 0.5 seconds of audio
		bytes_per_sample = av_get_bytes_per_sample(vdata->audio.codec_ctx->sample_fmt);
		channels = vdata->audio.codec_ctx->ch_layout.nb_channels;
		sample_rate = vdata->audio.codec_ctx->sample_rate;
		Uint32 max_queue = (Uint32)(290 * sample_rate * bytes_per_sample
				* channels); // 0.5 seconds
		if (queued < max_queue)
		{
			SDL_QueueAudio(vdata->audio.audio_dev, audio_buf, got);
		}
	}
	return (0);
}

int	allocate_video_frames(t_vdata *vdata)
{
	int	num_bytes;

	vdata->video.frame = av_frame_alloc();
	vdata->video.frame_rgb = av_frame_alloc();
	vdata->audio.frame = av_frame_alloc();
	if (!vdata->video.frame || !vdata->video.frame_rgb || !vdata->audio.frame)
		return (-1);
	num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, vdata->inf->win_w,
			vdata->inf->win_h, 1);
	vdata->video.buffer = av_malloc(num_bytes);
	if (!vdata->video.buffer)
		return (-1);
	av_image_fill_arrays(vdata->video.frame_rgb->data,
		vdata->video.frame_rgb->linesize, vdata->video.buffer, AV_PIX_FMT_RGB24,
		vdata->inf->win_w, vdata->inf->win_h, 1);
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

int	setup_video_codec(t_vdata *vdata)
{
	AVCodecParameters	*codecPar;

	codecPar = vdata->video.fmt_ctx->streams[vdata->video.video_index]->codecpar;
	vdata->video.codec = avcodec_find_decoder(codecPar->codec_id);
	if (!vdata->video.codec)
		return (-1);
	vdata->video.codec_ctx = avcodec_alloc_context3(vdata->video.codec);
	if (!vdata->video.codec_ctx)
		return (-1);
	if (avcodec_parameters_to_context(vdata->video.codec_ctx, codecPar) < 0)
		return (-1);
	if (avcodec_open2(vdata->video.codec_ctx, vdata->video.codec, NULL) < 0)
		return (-1);
	vdata->video.time_base = vdata->video.fmt_ctx->streams[vdata->video.video_index]->time_base;
	return (0);
}

int	setup_audio_codec(t_vdata *vdata)
{
	AVCodecParameters	*codecPar;

	if (vdata->audio.audio_index == -1)
		return (0);
	codecPar = vdata->video.fmt_ctx->streams[vdata->audio.audio_index]->codecpar;
	vdata->audio.codec = avcodec_find_decoder(codecPar->codec_id);
	if (!vdata->audio.codec)
		return (-1);
	vdata->audio.codec_ctx = avcodec_alloc_context3(vdata->audio.codec);
	if (!vdata->audio.codec_ctx)
		return (-1);
	if (avcodec_parameters_to_context(vdata->audio.codec_ctx, codecPar) < 0)
		return (-1);
	if (avcodec_open2(vdata->audio.codec_ctx, vdata->audio.codec, NULL) < 0)
		return (-1);
	vdata->audio.time_base = vdata->video.fmt_ctx->streams[vdata->audio.audio_index]->time_base;
	// Allocate audio frame if not already allocated
	if (!vdata->audio.frame)
	{
		vdata->audio.frame = av_frame_alloc();
		if (!vdata->audio.frame)
			return (-1);
	}
	return (0);
}

int	setup_audio_device(t_vdata *vdata)
{
	SDL_AudioSpec wanted_spec, obtained_spec;
	if (vdata->audio.audio_index == -1)
		return (0);
	wanted_spec.freq = vdata->audio.codec_ctx->sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = 2;
	wanted_spec.silence = 0;
	wanted_spec.samples = 1024;
	wanted_spec.callback = NULL;
	wanted_spec.userdata = vdata->audio.codec_ctx;
	vdata->audio.audio_dev = SDL_OpenAudioDevice(NULL, 0, &wanted_spec,
			&obtained_spec, 0);
	if (!vdata->audio.audio_dev)
		return (-1);
	SDL_PauseAudioDevice(vdata->audio.audio_dev, 0);
	vdata->audio.swr_ctx = swr_alloc();
	if (!vdata->audio.swr_ctx)
		return (-1);
	av_opt_set_chlayout(vdata->audio.swr_ctx, "in_chlayout",
		&vdata->audio.codec_ctx->ch_layout, 0);
	av_opt_set_chlayout(vdata->audio.swr_ctx, "out_chlayout",
		&(AVChannelLayout)AV_CHANNEL_LAYOUT_STEREO, 0);
	av_opt_set_int(vdata->audio.swr_ctx, "in_sample_rate",
		vdata->audio.codec_ctx->sample_rate, 0);
	av_opt_set_int(vdata->audio.swr_ctx, "out_sample_rate",
		vdata->audio.codec_ctx->sample_rate, 0);
	av_opt_set_sample_fmt(vdata->audio.swr_ctx, "in_sample_fmt",
		vdata->audio.codec_ctx->sample_fmt, 0);
	av_opt_set_sample_fmt(vdata->audio.swr_ctx, "out_sample_fmt",
		AV_SAMPLE_FMT_S16, 0);
	if (swr_init(vdata->audio.swr_ctx) < 0)
		return (-1);
	return (0);
}

int	init_format_context(const char *url, AVFormatContext **fmt_ctx)
{
	AVDictionary	*opts;

	opts = NULL;
	// Initialize the format context pointer to NULL
	*fmt_ctx = NULL;
	avformat_network_init();
	// Try opening with minimal options first
	if (avformat_open_input(fmt_ctx, url, NULL, NULL) != 0)
	{
		return (-1);
	}
	if (avformat_find_stream_info(*fmt_ctx, NULL) < 0)
	{
		avformat_close_input(fmt_ctx); // Clean up on error
		return (-1);
	}
	return (0);
}

int	initialize_video_player(t_vdata *vdata)
{
	vdata->video.fmt_ctx = NULL;
	if (init_format_context(vdata->video_path, &vdata->video.fmt_ctx) < 0)
		return (-1);
	vdata->audio.audio_index = find_stream_index(vdata->video.fmt_ctx,
			AVMEDIA_TYPE_AUDIO);
	vdata->video.video_index = find_stream_index(vdata->video.fmt_ctx,
			AVMEDIA_TYPE_VIDEO);
	if (vdata->video.video_index == -1)
		return (-1);
	if (setup_video_codec(vdata) < 0)
		return (-1);
	if (setup_audio_codec(vdata) < 0)
		return (-1);
	if (allocate_video_frames(vdata) < 0)
		return (-1);
	if (create_mlx_image(vdata) < 0)
		return (-1);
	if (setup_audio_device(vdata) < 0)
		return (-1);
	return (0);
}

void	cleanup_video_player(t_vdata *vdata)
{
	if (vdata->video.sws_ctx)
		sws_freeContext(vdata->video.sws_ctx);
	if (vdata->video.buffer)
		av_free(vdata->video.buffer);
	if (vdata->video.frame)
		av_frame_free(&vdata->video.frame);
	if (vdata->video.frame_rgb)
		av_frame_free(&vdata->video.frame_rgb);
	if (vdata->audio.frame)
		av_frame_free(&vdata->audio.frame);
	if (vdata->video.codec_ctx)
		avcodec_free_context(&vdata->video.codec_ctx);
	if (vdata->audio.codec_ctx)
		avcodec_free_context(&vdata->audio.codec_ctx);
	if (vdata->video.fmt_ctx)
		avformat_close_input(&vdata->video.fmt_ctx);
	if (vdata->image.img && vdata->inf->mlx)
		mlx_destroy_image(vdata->inf->mlx, vdata->image.img);
	if (vdata->audio.swr_ctx)
		swr_free(&vdata->audio.swr_ctx);
	if (vdata->audio.audio_dev)
		SDL_CloseAudioDevice(vdata->audio.audio_dev);
	avcodec_close(vdata->video.codec_ctx);
	SDL_Quit();
	avformat_network_deinit();
}

int	play_video(char *path)
{
	AVPacket	pkt;
	static int	video_initialized = 0;

	static t_vdata *vdata = NULL; // Make it static and initialize to NULL
	if (!video_initialized)
	{
		vdata = malloc(sizeof(t_vdata));
		if (!vdata)
			return (-1);
		// Initialize all pointers to NULL
		memset(vdata, 0, sizeof(t_vdata));
		vdata->inf = get_game();
		vdata->video_path = path;
		vdata->paused = false;
		if (initialize_video_player(vdata) < 0)
		{
			cleanup_video_player(vdata);
			free(vdata); // Clean up on failure
			vdata = NULL;
			return (-1);
		}
		video_initialized = 1;
	}
	if (get_key(KEY_SPACE, get_game())->press)
		vdata->paused = true;
	if (av_read_frame(vdata->video.fmt_ctx, &pkt) < 0)
	{
		cleanup_video_player(vdata);
		free(vdata); // Don't forget to free the allocated memory
		vdata = NULL;
		video_initialized = 0;
		return (1);
	}
	if (pkt.stream_index == vdata->video.video_index)
		process_video_packet(vdata, &pkt);
	else if (pkt.stream_index == vdata->audio.audio_index)
		process_audio_packet(vdata, &pkt);
	av_packet_unref(&pkt);
	return (0);
}
