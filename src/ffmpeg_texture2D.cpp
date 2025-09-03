#include "ffmpeg_texture2D.h"

extern "C" {
#include "ffmpeg/libavcodec/avcodec.h"
	int test(){
		const AVCodec *codec;
		codec = avcodec_find_decoder(AVCodecID::AV_CODEC_ID_MPEG4);
		return 223;
	}
}
void FFmpegTexture2D::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &FFmpegTexture2D::print_type);
}


void FFmpegTexture2D::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
	print_line(vformat("Type: %d", test()));
}

