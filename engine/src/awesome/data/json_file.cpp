#include "json_file.h"

#include <awesome/core/reflection.h>
#include <awesome/core/serialization.h>

#include "archive.h"

void JsonFile::save(const json::value& data, const std::filesystem::path& path)
{
	Archive archive(path, Archive::Mode::Write);
	archive << json::Serializer::to_string(data);
}

void JsonFile::save(IProtoClass* const proto, const std::filesystem::path& path)
{
	save(Serializer::instance().serialize(proto), path);
}

bool JsonFile::load(const std::filesystem::path& path, json::value& data)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	if (std::filesystem::exists(path))
	{
		return data = json::Deserializer::parse(read(path)), true;
	}
	return false;
}

bool JsonFile::load(const std::filesystem::path& path, IProtoClass* const proto)
{
	json::value data;
	if (load(path, data))
	{
		return Serializer::instance().deserialize(proto, data);
	}
	return false;
}