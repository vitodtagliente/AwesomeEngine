/// Copyright (c) Vito Domenico Tagliente
#pragma once

enum class AssetType
{

};

class Asset
{
public:
	Asset(AssetType type);

	inline AssetType getType() const { return m_type; }

private:
	AssetType m_type;
};