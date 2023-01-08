#include "text_asset.h"

#include <awesome/data/text_file.h>

void TextAsset::load(const std::filesystem::path& path)
{
	TextFile::load(path, data);
}