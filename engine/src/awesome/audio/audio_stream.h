/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>

#include <awesome/asset/audio_asset.h>
#include <awesome/core/uuid.h>

struct ma_sound;

struct AudioStream
{
public:
	AudioStream(const AudioAsset& asset);
	~AudioStream();

	enum class State
	{
		Paused,
		Playing,
		Stopped
	};

	void pause();
	void play();
	void resume();
	void stop();

	ma_sound* const data() const { return m_data; }
	const uuid& id() const { return m_id; }
	const std::filesystem::path& path() const { return m_path; }
	State state() const { return m_state; }

	bool isPlaying() const;

	void setLooping(bool value);
	void setPitch(float value);
	void setVolume(float value);

private:
	ma_sound* m_data{ nullptr };
	uuid m_id;
	std::filesystem::path m_path;
	State m_state{ State::Stopped };
};

typedef std::shared_ptr<AudioStream> AudioStreamPtr;