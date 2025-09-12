#include "gdffmpeg.h"

using namespace godot;

int FFmpegTexture::test(){
	codec = avcodec_find_decoder(AVCodecID::AV_CODEC_ID_MPEG4);
	return 0;
}

void FFmpegTexture::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("exists"), &FFmpegTexture::exists);
}

bool FFmpegTexture::exists() {
	if(test() == 0){
		return true;
	}
	else {
		return false;
	}
}

void FFmpeg::_bind_methods() {
	return;
}
