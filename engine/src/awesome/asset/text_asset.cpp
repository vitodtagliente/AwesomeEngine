#include "text_asset.h"

#include <awesome/data/text_file.h>

bool TextAsset::load(const std::filesystem::path& _path)
{
	return TextFile::load(_path, data);
}

bool TextAsset::save(const std::filesystem::path& _path) const
{
	return TextFile::save(data, _path), true;
}
