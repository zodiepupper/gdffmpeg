#pragma once

#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/variant/variant.hpp"

extern "C" {
#include "ffmpeg/libavcodec/codec.h"
}

using namespace godot;
// awwooo
class FFmpegTexture : public Texture2D {
	GDCLASS(FFmpegTexture, Texture2D)

protected:
	static void _bind_methods();

public:
	FFmpegTexture() = default;
	~FFmpegTexture() override = default;
	const AVCodec *codec;
	int test();
	bool exists();
//	void print_type(const Variant &p_variant) const;
};


class FFmpeg : public Object {
	GDCLASS(FFmpeg, Object)

	protected:
		static void _bind_methods();

	public:
		FFmpeg() = default;
		~FFmpeg() override = default;
};

class GDAVCodec : public RefCounted {
	GDCLASS(GDAVCodec, RefCounted)

	protected:
		static void _bind_methods();

	public:
		GDAVCodec() = default;
		~GDAVCodec() override = default;
};
