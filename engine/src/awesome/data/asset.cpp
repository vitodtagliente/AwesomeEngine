#include "asset.h"

#include <fstream>
#include <map>

std::map<Asset::Type, std::set<std::string>> Asset::s_filetypes{
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
	, filename()
{

}

Asset::Asset(const Type type)
	: id()
	, type(type)
	, filename()
{

}

Asset::Asset(const Type type, const uuid& id)
	: id(id)
	, type(type)
	, filename()
{

}

Asset::Asset(const Asset& asset)
	: id(asset.id)
	, type(asset.type)
	, filename(asset.filename)
{

}

Asset& Asset::operator= (const Asset& other)
{
	id = other.id;
	type = other.type;
	filename = other.filename;
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

json::value Asset::serialize() const
{
	return json::object({
		{"id", ::serialize(id)},
		{"type", static_cast<int>(type)}
		});
}

void Asset::deserialize(const json::value& value)
{
	::deserialize(value["id"], id);
	type = static_cast<Type>(value["type"].as_number(0).as_int());
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
	asset.filename = filename;
	std::string content = read(filename);
	json::value value = json::Deserializer::parse(content);
	asset.deserialize(value);
	return asset;
}

bool Asset::isAsset(const std::filesystem::path& filename)
{
	return filename.extension().string() == Extension;
}

const std::set<std::string>& Asset::getExtensions(const Type type)
{
	return s_filetypes[type];
}

Asset::Type Asset::getTypeByExtension(const std::string& extension)
{
	for (const auto& pair : s_filetypes)
	{
		if (pair.second.find(extension) != pair.second.end())
		{
			return pair.first;
		}
	}
	return Asset::Type::None;
}

REFLECT_IMP(Asset)