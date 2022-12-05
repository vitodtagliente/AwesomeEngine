#include "asset.h"

#include <fstream>
#include <map>

#include <awesome/core/serialization.h>
#include <awesome/data/archive.h>
#include <awesome/encoding/json.h>

std::map<Asset::Type, std::vector<std::string>> Asset::s_filetypes{
	{ Asset::Type::Image, {".png", ".jpg", ".jpeg", ".bmp"} },
	{ Asset::Type::Prefab, {".prefab"} },
	{ Asset::Type::Scene, {".scene"} },
	{ Asset::Type::Sprite, {".sprite"} },
	{ Asset::Type::SpriteAnimation, {".spriteanim"} },
	{ Asset::Type::Text, {".txt", ".md", ".shader", ".ini", ".cfg"} }
};

Asset::Asset()
	: descriptor()
{

}

Asset::Asset(const Descriptor& descriptor)
	: descriptor(descriptor)
{
}

bool Asset::operator==(const Asset& other) const
{
	return descriptor.id == other.descriptor.id;
}

bool Asset::operator!=(const Asset& other) const
{
	return descriptor.id != other.descriptor.id;
}

bool Asset::isAsset(const std::filesystem::path& filename)
{
	return filename.extension().string() == Extension;
}

const std::vector<std::string>& Asset::getExtensionsByType(const Type type)
{
	static const std::vector<std::string> s_notFound;

	const auto& it = s_filetypes.find(type);
	if (it != s_filetypes.end())
	{
		return it->second;
	}
	return s_notFound;
}

const std::string& Asset::getExtensionByType(const Type type)
{
	static const std::string s_notFound;

	const auto& extensions = getExtensionsByType(type);
	if (!extensions.empty())
	{
		return extensions.at(0);
	}
	return s_notFound;
}

Asset::Type Asset::getTypeByExtension(const std::string& extension)
{
	for (const auto& pair : s_filetypes)
	{
		if (std::find(pair.second.begin(), pair.second.end(), extension) != pair.second.end())
		{
			return pair.first;
		}
	}
	return Asset::Type::None;
}

Asset::Descriptor::Descriptor()
	: id()
	, path()
	, type(Asset::Type::None)
{
}

Asset::Descriptor::Descriptor(Type type)
	: id()
	, path()
	, type(type)
{
}

Asset::Descriptor::Descriptor(const Descriptor& other)
	: id(other.id)
	, path(other.path)
	, type(other.type)
{
}

Asset::Descriptor& Asset::Descriptor::operator=(const Descriptor& other)
{
	id = other.id;
	path = other.path;
	type = other.type;
	return *this;
}

bool Asset::Descriptor::operator==(const Descriptor& other) const
{
	return id == other.id;
}

bool Asset::Descriptor::operator!=(const Descriptor& other) const
{
	return id != other.id;
}

Asset::Descriptor Asset::Descriptor::load(const std::filesystem::path& filename)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	Asset::Descriptor descriptor;
	descriptor.path = filename;
	std::string content = read(filename);
	json::value value = json::Deserializer::parse(content);
	{
		Deserializer::deserialize(value.safeAt("id"), descriptor.id);
		stringToEnum(value["type"].as_string(""), descriptor.type);
	}
	return descriptor;
}

void Asset::Descriptor::save(const std::filesystem::path& filename)
{
	const json::value& data = json::object({
		   {"id", Serializer{}.serialize(id)},
		   {"type", enumToString(type)}
		});

	path = filename;
	Archive archive(filename, Archive::Mode::Write);
	archive << json::Serializer::to_string(data);
}

std::filesystem::path Asset::Descriptor::getDataPath() const
{
	return path.string().substr(0, path.string().length() - std::string(Asset::Extension).length());
}
