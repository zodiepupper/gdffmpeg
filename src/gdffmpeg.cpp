#include "gdffmpeg.h"

using namespace godot;

void FFmpegTexture::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("exists"), &FFmpegTexture::exists);
}

bool FFmpegTexture::exists() {
	return true;
}

bool decode_from_bytes(PackedByteArray bytes) {
	return true;
}

void FFmpeg::_bind_methods() {
	return;
}

static void _decode(AVCodecContext *dec_ctx, AVFrame *frame, AVPacket *pkt, const char *filename)
{
    char buf[1024];
    int av_send_packet;

    av_send_packet = avcodec_send_packet(dec_ctx, pkt);
    if (av_send_packet < 0) {
        fprintf(stderr, "Error sending a packet for decoding\n");
        exit(1);
    }

    while (av_send_packet >= 0) {
        av_send_packet = avcodec_receive_frame(dec_ctx, frame);
        if (av_send_packet == AVERROR(EAGAIN) || av_send_packet == AVERROR_EOF)
            return;
        else if (av_send_packet < 0) {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }

        //printf("saving frame %3"PRId64"\n", dec_ctx->frame_num);
        fflush(stdout);

        /* the picture is allocated by the decoder. no need to
           free it */
        //snprintf(buf, sizeof(buf), "%s-%"PRId64, filename, dec_ctx->frame_num);
        //pgm_save(frame->data[0], frame->linesize[0],
                 //frame->width, frame->height, buf);
    }
}

#define INBUF_SIZE 4096

int main(int argc, char **argv)
{
    const char *filename, *outfilename;
    const AVCodec *codec;
    AVCodecParserContext *parser;
    AVCodecContext *avcodec_context3 = NULL;
    FILE *file;
    AVFrame *frame;
    uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    uint8_t *data;
    size_t   data_size;
    int av_send_packet;
    int eof;
    AVPacket *pkt;

    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n"
                "And check your input file is encoded by mpeg1video please.\n", argv[0]);
        exit(0);
    }
    filename    = argv[1];
    outfilename = argv[2];

    pkt = av_packet_alloc();
    if (!pkt)
        exit(1);

    /* set end of buffer to 0 (this ensures that no overreading happens for damaged MPEG streams) */
    memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    /* find the MPEG-1 video decoder */
    codec = avcodec_find_decoder(AV_CODEC_ID_MPEG1VIDEO);
    if (!codec) {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }

    parser = av_parser_init(codec->id);
    if (!parser) {
        fprintf(stderr, "parser not found\n");
        exit(1);
    }

    avcodec_context3 = avcodec_alloc_context3(codec);
    if (!avcodec_context3) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    /* For some codecs, such as msmpeg4 and mpeg4, width and height
       MUST be initialized there because this information is not
       available in the bitstream. */

    /* open it */
    if (avcodec_open2(avcodec_context3, codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }

    file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }

    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }

    do {
        /* read raw data from the input file */
        data_size = fread(inbuf, 1, INBUF_SIZE, file);
        if (ferror(file))
            break;
        eof = !data_size;

        /* use the parser to split the data into frames */
        data = inbuf;
        while (data_size > 0 || eof) {
            av_send_packet = av_parser_parse2(parser, avcodec_context3, &pkt->data, &pkt->size,
                                   data, data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
            if (av_send_packet < 0) {
                fprintf(stderr, "Error while parsing\n");
                exit(1);
            }
            data      += av_send_packet;
            data_size -= av_send_packet;

            if (pkt->size)
                _decode(avcodec_context3, frame, pkt, outfilename);
            else if (eof)
                break;
        }
    } while (!eof);

    /* flush the decoder */
    _decode(avcodec_context3, frame, NULL, outfilename);

    fclose(file);

    av_parser_close(parser);
    avcodec_free_context(&avcodec_context3);
    av_frame_free(&frame);
    av_packet_free(&pkt);

    return 0;
}
