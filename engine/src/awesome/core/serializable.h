/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/encoding/json.h>

struct ISerializable
{
	virtual json::value serialize() const = 0;
	virtual void deserialize(const json::value& value) = 0;
};