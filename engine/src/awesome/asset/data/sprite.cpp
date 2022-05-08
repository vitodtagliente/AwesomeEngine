#include "sprite.h"

#include <fstream>

#include <awesome/core/serialization.h>
#include <awesome/asset/asset_library.h>
#include <awesome/data/archive.h>
#include <awesome/encoding/json.h>

Sprite::Sprite()
	: image()
	, rect()
{
}

Sprite::Sprite(const ImageAssetPtr& image)
	: image(image)
	, rect()
{
}

Sprite::Sprite(const ImageAssetPtr& image, const graphics::TextureRect& rect)
	: image(image)
	, rect(rect)
{
}

Sprite::Sprite(const Sprite& other)
	: image(other.image)
	, rect(other.rect)
{
}

Sprite::~Sprite()
{
}

Sprite Sprite::load(const std::filesystem::path& path)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	Sprite sprite;
	json::value data = json::Deserializer::parse(read(path));

	const uuid id(data.safeAt("image").as_string(""));
	sprite.image = AssetLibrary::instance().find<ImageAsset>(id);
	deserialize(data.safeAt("rect"), sprite.rect);	
	return sprite;
}

void Sprite::save(const std::filesystem::path& path)
{
	json::value data = json::object({
		{"image", image ? static_cast<std::string>(image->descriptor.id) : ""},
		{"rect", serialize(rect)}
		});

	Archive ar(path, Archive::Mode::Write);
	ar << json::Serializer::to_string(data);
}

Sprite& Sprite::operator=(const Sprite& other)
{
	image = other.image;
	rect = other.rect;
	return *this;
}

bool Sprite::operator==(const Sprite& other) const
{
	return image == other.image && rect == other.rect;
}

bool Sprite::operator!=(const Sprite& other) const
{
	return image != other.image || rect != other.rect;
}
