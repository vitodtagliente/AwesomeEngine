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
	: id()
	, type(Type::None)
	, path()
{

}

Asset::Asset(const Type type)
	: id()
	, type(type)
	, path()
{

}

Asset::Asset(const Type type, const uuid& id)
	: id(id)
	, type(type)
	, path()
{

}

Asset::Asset(const Asset& asset)
	: id(asset.id)
	, type(asset.type)
	, path(asset.path)
{

}

Asset& Asset::operator= (const Asset& other)
{
	id = other.id;
	type = other.type;
	path = other.path;
	return *this;
}

bool Asset::operator== (const Asset& other) const
{
	return id == other.id;
}

bool Asset::operator!= (const Asset& other) const
{
	return id != other.id;
}

Asset Asset::load(const std::filesystem::path& filename)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	Asset asset;
	asset.path = filename;
	std::string content = read(filename);
	json::value value = json::Deserializer::parse(content);
	{
		deserialize(value["id"], asset.id);
		asset.type = static_cast<Type>(value["type"].as_number(0).as_int());
	}
	return asset;
}

void Asset::save(const std::filesystem::path& filename)
{
	const json::value& data = json::object({
		{"id", serialize(id)},
		{"type", static_cast<int>(type)}
		});

	path = filename;
	Archive archive(filename, Archive::Mode::Write);
	archive << json::Serializer::to_string(data);
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

REFLECT_IMP(Asset)