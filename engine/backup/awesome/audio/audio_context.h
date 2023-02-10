/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <miniaudio.h>

#include <awesome/core/singleton.h>

#include "sound.h"

class AudioContext final : public Singleton<AudioContext>
{
public:
	friend class Audio;

	bool load(const std::filesystem::path& path, Sound& sound);
	void play(Sound& sound);

private:
	ma_engine m_engine;
};