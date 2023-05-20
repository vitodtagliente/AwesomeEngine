/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "audio_generated.h"

ENUM()
enum class AudioType : int
{
	flac,
	mp3,
	wav
};

struct Audio
{
	AudioType type;
};