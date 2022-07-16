#include "sprite_animation.h"

#include <awesome/asset/asset_library.h>
#include <awesome/data/archive.h>
#include <awesome/encoding/json.h>

SpriteAnimation::SpriteAnimation()
	: startingFrame()
	, frames()
{
}

SpriteAnimation::SpriteAnimation(const std::vector<Frame>& frames)
	: startingFrame()
	, frames(frames)
{
}

SpriteAnimation::SpriteAnimation(const std::vector<Frame>& frames, const int startingFrame)
	: startingFrame(startingFrame)
	, frames(frames)
{
}

SpriteAnimation SpriteAnimation::load(const std::filesystem::path& path)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	SpriteAnimation animation;
	json::value data = json::Deserializer::parse(read(path));
	animation.startingFrame = static_cast<unsigned int>(data.safeAt("startingFrame").as_number(0).as_int());
	if (data.contains("frames"))
	{
		const json::value::array_t& jframes = data["frames"].as_array();
		for (const json::value& jframe : jframes)
		{
			Frame frame;			
			const uuid id(jframe.safeAt("sprite").as_string(""));
			frame.sprite = AssetLibrary::instance().find<SpriteAsset>(id);
			frame.duration = jframe.safeAt("duration").as_number(.1f).as_double();
			animation.frames.push_back(frame);
		}
	}
	return animation;
}

void SpriteAnimation::save(const std::filesystem::path& path)
{
	json::value list = json::array();
	for (const Frame& frame : frames)
	{
		list.push_back(json::object({
			{"sprite", static_cast<std::string>(frame.sprite ? frame.sprite->descriptor.id : uuid::Invalid)},
			{"duration", frame.duration}
			}));
	}

	json::value data = json::object({
			{"startingFrame", static_cast<int>(startingFrame)},
			{"frames", list}
		});

	Archive ar(path, Archive::Mode::Write);
	ar << json::Serializer::to_string(data);
}

SpriteAnimation& SpriteAnimation::operator=(const SpriteAnimation& other)
{
	frames = other.frames;
	startingFrame = other.startingFrame;
	return *this;
}

bool SpriteAnimation::operator==(const SpriteAnimation& other) const
{
	return startingFrame == other.startingFrame && frames == other.frames;
}

bool SpriteAnimation::operator!=(const SpriteAnimation& other) const
{
	return startingFrame != other.startingFrame || frames != other.frames;
}
