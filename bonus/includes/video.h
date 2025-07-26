#ifndef VIDEO_H
# define VIDEO_H

# include "cub.h"
# include <libavcodec/avcodec.h>
# include <libavformat/avformat.h>
# include <libavutil/channel_layout.h>
# include <libavutil/imgutils.h>
# include <libavutil/opt.h>
# include <libswresample/swresample.h>
# include <libswscale/swscale.h>

typedef struct s_video_state
{
	AVFormatContext		*fmt_ctx;
	AVCodecContext		*codec_ctx;
	const AVCodec		*codec;
	struct SwsContext	*sws_ctx;
	AVFrame				*frame;
	AVFrame				*frame_rgb;
	uint8_t				*buffer;
	int					video_index;
	AVRational			time_base;
}						t_video_state;

typedef struct s_audio_state
{
	AVCodecContext		*codec_ctx;
	const AVCodec		*codec;
	struct SwrContext	*swr_ctx;
	AVFrame				*frame;
	int					audio_index;
	SDL_AudioDeviceID	audio_dev;
	double				audio_time_written;
	AVRational			time_base;

}						t_audio_state;

typedef struct s_vdata
{
	t_game				*inf;
	bool				paused;
	char				*video_path;
	double				sync_threshold;
	t_video_state		video;
	t_audio_state		audio;
	t_image				image;
}						t_vdata;

// Function prototypes
int						play_video(char *path);
int						setup_audio_codec(t_vdata *vdata);
int						setup_audio_device(t_vdata *vdata);
int						find_stream_index(AVFormatContext *fmt_ctx,
							enum AVMediaType type);
void					draw_frame_to_mlx(t_image *img, AVFrame *frame_rgb);
void					cleanup_video_player(t_vdata *vdata);

#endif