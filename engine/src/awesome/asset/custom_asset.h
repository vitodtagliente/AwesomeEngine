/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/core/reflection.h>

#include "base_asset.h"

template <typename T = Type>
struct CustomAsset : public BaseAsset<Asset::Type::Custom, std::unique_ptr<T>>
{
	CustomAsset(const Asset::Descriptor& descriptor)
		: BaseAsset(descriptor)
	{

	}
};