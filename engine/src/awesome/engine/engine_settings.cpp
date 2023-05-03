#include "engine_settings.h"

#include <awesome/data/type_file.h>

void EngineSettings::save() const
{
	TypeFile::save(*this, path);
}

bool EngineSettings::load(const std::filesystem::path& _path)
{
	path = _path;
	if (!std::filesystem::exists(_path)) return false;

	return TypeFile::load(_path, *this);
}