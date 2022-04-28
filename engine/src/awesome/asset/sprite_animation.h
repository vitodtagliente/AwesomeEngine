/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <vector>

#include "sprite_asset.h"

struct SpriteAnimation final
{
	struct Frame final
	{
		Frame()
			: sprite()
			, duration(1.0f)
		{}

		Frame(const SpriteAssetPtr sprite, const double duration)
			: sprite(sprite)
			, duration(duration)
		{}

		bool operator== (const Frame& other) const
		{
			return duration == other.duration && sprite == other.sprite;
		}

		SpriteAssetPtr sprite;
		double duration;
	};

	SpriteAnimation();
	SpriteAnimation(const std::vector<Frame>& frames);
	SpriteAnimation(const std::vector<Frame>& frames, int startingFrame);

	static SpriteAnimation load(const std::filesystem::path& filename);
	void save(const std::filesystem::path& filename);

	SpriteAnimation& operator= (const SpriteAnimation& other);
	bool operator== (const SpriteAnimation& other) const;
	bool operator!= (const SpriteAnimation& other) const;

	unsigned int startingFrame;
	std::vector<Frame> frames;
};