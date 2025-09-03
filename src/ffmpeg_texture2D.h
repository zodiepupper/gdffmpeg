#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;
// awwooo
class FFmpegTexture2D : public RefCounted {
	GDCLASS(FFmpegTexture2D, RefCounted)

protected:
	static void _bind_methods();

public:
	FFmpegTexture2D() = default;
	~FFmpegTexture2D() override = default;

	void print_type(const Variant &p_variant) const;
};
