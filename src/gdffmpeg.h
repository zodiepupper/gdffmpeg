#pragma once

// this is an interface to use ffmpeg within godot
// the goal is to provide a simplified FFmpegTexture
// where the end user needs to put in minimal effort
// and provide wrappers for everything else to be
// accessible from gdscript or whatever script lang
// the user is using for their work in godot
//
// for contributions:
// make sure code fits the style and is well organized
// and reabable. it is very important that our codebases
// remain accessible and readable for anyone who may need
// to modify or learn from the codebase in the future,
// even if they do not have prior knowledge of the systems

#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/variant/variant.hpp"
#include <stdio.h>

extern "C" {
#include "ffmpeg/libavcodec/codec.h"
#include "ffmpeg/libavcodec/avcodec.h"
}

using namespace godot;

// wrapper class for accessing AVCodec functionality from within godot

class GDAVCodec : public Ref<T> {
	GDCLASS(GDAVCodec, Ref<T>)

	protected:
		static void _bind_methods();

	public:
		GDAVCodec() = default;
		~GDAVCodec() override = default;
		static int find_decoder();

		const AVCodec *codec;

};

// wrapper class for accessing AVCodecParserContext functionality from within godot

class GDAVCodecParserContext : public RefCounted {
	GDCLASS(GDAVCodecParserContext, RefCounted)

	protected:
		static void _bind_methods();

	public:
		//GDAVCodecParserContext() = default;
		~GDAVCodecParserContext() override = default;

		AVCodecParserContext *parser_context;

};

// wrapper class for accessing AVCodecParserContext functionality from within godot

class GDAVFrame : public RefCounted {
	GDCLASS(GDAVFrame, RefCounted)

	protected:
		static void _bind_methods();

	public:
		//GDAVCodecParserContext() = default;
		~GDAVFrame() override = default;

		AVFrame *avframe;

};

// wrapper class for AVCodecContext

class GDAVCodecContext : public RefCounted {
	GDCLASS(GDAVCodecContext, RefCounted)

	protected:
		static void _bind_methods();

	public:
		//GDAVCodecContext();
		~GDAVCodecContext() override = default;

		AVCodecContext *codec_context = new AVCodecContext;
};

class GDAVPacket : public RefCounted {
	GDCLASS(GDAVPacket, RefCounted)

	protected:
		static void _bind_methods();

	public:
		AVPacket *avpacket = new AVPacket;
};

// this is a simplified helper utility for end users
// to shove a thing to be decoded into and get an
// AudioStream and a Textuere out of it, so they can
// easily bypass the complexity of using ffmpeg

class FFmpegTexture : public Texture2D {
	GDCLASS(FFmpegTexture, Texture2D)

protected:
	static void _bind_methods();

public:
	FFmpegTexture() = default;
	~FFmpegTexture() override = default;
	const AVCodec *codec;
	bool exists();
	bool decode_from_bytes(PackedByteArray bytes);
	void decode_mp4(GDAVCodecContext dec_ctx, GDAVFrame frame, GDAVPacket pkt, String filename);
};

// the root class that provides access to constants and variables
// relevant to using FFmpeg in godot

class FFmpeg : public Object {
	GDCLASS(FFmpeg, Object)

	protected:
		static void _bind_methods();

	public:
		FFmpeg() = default;
		~FFmpeg() override = default;
};

