/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

typedef int PlayerIndex;

class Player
{
public:
	
	PlayerIndex getIndex() const { return m_index; }

private:
	PlayerIndex m_index;

	static std::unique_ptr<Player> s_localPlayer;
};