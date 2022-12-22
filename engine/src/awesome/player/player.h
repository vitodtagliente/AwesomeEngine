/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/entity.h>

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

class Player : public Entity
{
public:
	Player() = default;
	virtual ~Player() = default;

	virtual void prepareToSpawn() override;
	virtual void prepareToDestroy() override;

	inline class PlayerController* const getController() const { return m_controller; }
	inline PlayerIndex getIndex() const { return m_index; }

	static Player* const initialize(PlayerIndex index, const std::string& controller, const std::string& state);
	static Player* const getLocalPlayer() { return getPlayer(PlayerIndex::Player0); }
	static Player* const getPlayer(PlayerIndex index);
	static const std::vector<Player*>& getPlayers() { return s_instances; }

	static const std::string EntityTag;

private:
	class PlayerController* m_controller{ nullptr };
	PlayerIndex m_index{ PlayerIndex::Invalid };

	static std::vector<Player*> s_instances;
};