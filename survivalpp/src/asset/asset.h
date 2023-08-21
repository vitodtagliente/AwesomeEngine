#pragma once

#include <filesystem>

#include "core/uuid.h"

struct Asset
{
	uuid id;
	std::filesystem::path path;
};