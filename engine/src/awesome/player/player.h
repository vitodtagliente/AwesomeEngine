/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <vector>
#include <string>

#include "player_controller.h"

#include "player_generated.h"

ENUM()
enum class PlayerIndex : int
{
	Invalid = -1,
	Player0 = 0,
	Player1 = 1,
	Player2,
	Player3,
	Player4,
	Player5,
	Player6,
	Player7,
	Count
};

class Player
{
public:
	Player(PlayerIndex index, PlayerController* const controller, PlayerState* const state);
	~Player();

	void init();
	void update(double deltaTime);

	PlayerController* const getController() const { return m_controller.get(); }
	PlayerIndex getIndex() const { return m_index; }

	static Player* const getLocalPlayer() { return getPlayer(PlayerIndex::Player0); }
	static Player* const getPlayer(PlayerIndex index);
	static const std::vector<Player*>& getPlayes() { return s_instances; }

private:
	std::unique_ptr<PlayerController> m_controller;
	PlayerIndex m_index{ PlayerIndex::Invalid };

	static std::vector<Player*> s_instances;
};