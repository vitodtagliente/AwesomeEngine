#include "json_file.h"

#include "text_file.h"

void JsonFile::save(const json::value& data, const std::filesystem::path& path)
{
	TextFile::save(json::Serializer::to_string(data), path);
}

bool JsonFile::load(const std::filesystem::path& path, json::value& data)
{
	if (std::filesystem::exists(path))
	{
		std::string content;
		if (TextFile::load(path, content))
		{
			return data = json::Deserializer::parse(content), true;
		}		
	}
	return false;
}
