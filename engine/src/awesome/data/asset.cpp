#include "asset.h"

#include <fstream>

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
		{"id", static_cast<std::string>(id)},
		{"type", static_cast<int>(type)}
		});
}

void Asset::deserialize(const json::value& value)
{
	if (value.contains("id"))
	{
		id = uuid(value["id"].as_string());
	}
	if (value.contains("type"))
	{
		type = static_cast<Type>(value["type"].as_number().as_int());
	}
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

REFLECT_IMP(Asset)