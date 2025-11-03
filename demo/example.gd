extends TextureRect

var fftex := FFmpegTexture.new()
var ffmpeg := FFmpeg.new()

func _ready() -> void:
	print(fftex.exists())
	
	print(fftex)
	pass
