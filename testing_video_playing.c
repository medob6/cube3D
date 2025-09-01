#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/channel_layout.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>

int	main(int argc, char *argv[])
{
	AVFormatContext *pFormatCtx = NULL;

	if (avformat_open_input(&pFormatCtx, argv[1], NULL, 0) != 0)
		return (-1);
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
		return (-1);

	// Dump information about file onto standard error
	av_dump_format(pFormatCtx, 0, argv[1], 0);

	return (0);
}