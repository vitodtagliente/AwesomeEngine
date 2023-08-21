#pragma once

#include <string>
#include <memory>
#include <queue>
#include <vector>

#include "ecs/entity_ptr.h"

class PlayerController
{
public:
	inline const EntityPtr& entity() const { return m_entity; }
	
	void possess(Entity* const entity);
	void unpossess();

	virtual void update(double /*delta_time*/) {};

protected:
	EntityPtr m_entity;
};

struct Player
{
	typedef std::size_t index_t;

	inline bool is_local() const { return index == 0; }

	std::string name;
	index_t index;
	std::unique_ptr<PlayerController> controller;
};

class PlayerManager
{
public:
	inline static const std::vector<Player>& players()
	{ 
		return s_players; 
	}

	static Player& local();

	Player& connect();
	void disconnect(Player::index_t index);

	void update(double delta_time);

private:
	static inline std::vector<Player> s_players;
	static inline std::queue<Player::index_t> s_recycled_indexes;
};