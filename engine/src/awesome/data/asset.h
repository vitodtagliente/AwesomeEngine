/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>

class Asset
{
public:

	enum class Type
	{
		Image,
		Prefab
	};

	Asset(Type type);

	inline const uuid& getId() const { return m_id; }
	inline Type getType() const { return m_type; }

private:
	uuid m_id;
	Type m_type;
};

template <typename T>
class BaseAsset : public Asset
{
public:


private:
	

};