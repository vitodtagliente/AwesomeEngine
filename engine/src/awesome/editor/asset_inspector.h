/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/asset_database.h>
#include <awesome/core/reflection.h>

#include "asset_inspector_generated.h"

CLASS()
struct AssetInspector : public IType
{
	AssetInspector() = default;
	virtual ~AssetInspector() = default;

	virtual bool canInspect(int /*asset_type*/) const { return false; }
	virtual char* const getTitle() const { return ""; }
	virtual void inspect(const AssetRecord& /*record*/) {}

	GENERATED_BODY()
};