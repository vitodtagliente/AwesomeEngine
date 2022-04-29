/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/core/uuid.h>

class Player
{
public:
	Player() = default;

	inline const uuid& getId() const { return m_id; }

private:
	uuid m_id;
};