#include "type_file.h"

#include "text_file.h"

void TypeFile::save(const IType& data, const std::filesystem::path& path)
{
	TextFile::save(data.to_json(), path);
}

bool TypeFile::load(const std::filesystem::path& path, IType& data)
{
	if (std::filesystem::exists(path))
	{
		std::string content;
		if (TextFile::load(path, content))
		{
			return data.from_json(content), true;
		}
	}
	return false;
}
