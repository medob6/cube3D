// #ifndef VIDEO_BS_H
// # define VIDEO_BS_H

// # include "cub_bs.h"
// // # include <libavcodec/avcodec.h>
// // # include <libavformat/avformat.h>
// // # include <libavutil/channel_layout.h>
// // # include <libavutil/imgutils.h>
// // # include <libavutil/opt.h>
// // # include <libswresample/swresample.h>
// // # include <libswscale/swscale.h>

// # define INITIAL_BUFFER_SIZE 5

// typedef struct s_audio_convert
// {
// 	AVCodecContext		*ctx;
// 	AVFrame				*frame;
// 	uint8_t				*out_buf;
// 	int					out_buf_size;
// 	struct SwrContext	*swr_ctx;
// }						t_audio_convert;

// typedef struct s_audio_decode
// {
// 	AVCodecContext		*ctx;
// 	AVPacket			*pkt;
// 	AVFrame				*frame;
// 	uint8_t				*out_buf;
// 	int					out_buf_size;
// 	struct SwrContext	*swr_ctx;
// }						t_audio_decode;

// typedef struct s_audio_process
// {
// 	uint8_t				audio_buf[192000 * 3 / 2];
// 	int					out_size;
// }						t_audio_process;

// typedef struct s_video_state
// {
// 	AVFormatContext		*fmt_ctx;
// 	AVCodecContext		*codec_ctx;
// 	const AVCodec		*codec;
// 	struct SwsContext	*sws_ctx;
// 	AVFrame				*frame;
// 	AVFrame				*frame_rgb;
// 	uint8_t				*buffer;
// 	int					video_index;
// 	AVRational			time_base;
// }						t_video_state;

// typedef struct s_audio_state
// {
// 	AVCodecContext		*codec_ctx;
// 	const AVCodec		*codec;
// 	struct SwrContext	*swr_ctx;
// 	AVFrame				*frame;
// 	int					audio_index;
// 	SDL_AudioDeviceID	audio_dev;
// 	double				audio_time_written;
// 	AVRational			time_base;
// 	Uint64				total_audio_bytes_sent;

// }						t_audio_state;

// typedef struct s_vdata
// {
// 	t_game				*inf;
// 	char				*video_path;
// 	double				sync_threshold;
// 	t_video_state		video;
// 	t_audio_state		audio;
// 	t_image				image;
// 	uint64_t			total_audio_bytes_sent;
// 	int					av_synced;
// }						t_vdata;

// /* Main functions - video.c */
// int						find_stream_index(AVFormatContext *fmt_ctx,
// 							enum AVMediaType type);
// void					draw_frame_to_mlx(t_image *img, AVFrame *frame_rgb);
// int						decode_audio_frame(t_audio_decode *decode);
// double					get_audio_clock(t_vdata *vdata);
// int						process_video_packet(t_vdata *vdata, AVPacket *pkt);
// int						process_audio_packet(t_vdata *vdata, AVPacket *pkt);
// int						allocate_video_frames(t_vdata *vdata);
// int						create_mlx_image(t_vdata *vdata);
// int						play_video(char *path);

// /* Helper functions - video_utils.c */
// int						create_color(uint8_t *src, int x);
// t_audio_convert			init_audio_convert(t_audio_decode *decode);
// double					calculate_seconds_queued(t_vdata *vdata,
// 							uint32_t bytes_queued);
// int						decode_audio_frame_wrapper(t_vdata *vdata,
// 							AVPacket *pkt, t_audio_process *proc);
// void					handle_decoded_audio(t_vdata *vdata, uint8_t *audio_buf,
// 							int got);
// uint32_t				calculate_max_queue_size(t_vdata *vdata);
// int						initialize_player_data(t_vdata **vdata, char *path);
// int						handle_video_end(t_vdata **vdata,
// 							int *video_initialized);
// int						process_packet_by_type(t_vdata *vdata, AVPacket *pkt);

// /* Codec functions - video_codec.c */
// int						setup_video_codec(t_vdata *vdata);
// int						setup_audio_codec(t_vdata *vdata);
// int						init_format_context(const char *url,
// 							AVFormatContext **fmt_ctx);
// int						initialize_video_player(t_vdata *vdata);

// /* Audio device functions - video_audio.c */
// int						setup_audio_device(t_vdata *vdata);

// /* Cleanup functions - video_cleanup.c */
// void					cleanup_video_player(t_vdata *vdata);

// #endif
