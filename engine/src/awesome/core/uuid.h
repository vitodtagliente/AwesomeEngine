/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include "reflection.h"

#include "uuid_generated.h"

CLASS()
struct uuid final : public IType
{
	uuid();
	uuid(const std::string& value);
	uuid(const uuid& other);
	~uuid() = default;

	bool operator== (const uuid& other) const;
	bool operator!= (const uuid& other) const;
	bool operator< (const uuid& other) const;

	static const uuid Invalid;

	PROPERTY() std::string value;

	GENERATED_BODY()
};