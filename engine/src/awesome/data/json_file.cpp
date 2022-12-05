#include "json_file.h"

#include <awesome/core/reflection.h>
#include <awesome/core/serialization.h>

#include "archive.h"

void JsonFile::save(const json::value& data, const std::filesystem::path& path)
{
	Archive archive(path, Archive::Mode::Write);
	archive << json::Serializer::to_string(data);
}

void JsonFile::save(const IType& type, const std::filesystem::path& path)
{
	save(Serializer{}.serialize(type), path);
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

bool JsonFile::load(const std::filesystem::path& path, IType& type)
{
	json::value data;
	if (load(path, data))
	{
		return Deserializer{}.deserialize(data, type);
	}
	return false;
}