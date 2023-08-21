#include "player.h"

void PlayerController::possess(Entity* const entity)
{
	m_entity = entity;
}

void PlayerController::unpossess()
{
	m_entity.reset();
}

Player& PlayerManager::local()
{
	return s_players[0];
}

Player& PlayerManager::connect()
{
	Player& player = s_players.emplace_back();
	if (!s_recycled_indexes.empty())
	{
		player.index = s_recycled_indexes.back();
		s_recycled_indexes.pop();
	}
	else
	{
		player.index = s_players.size() - 1;
	}
	return player;
}

void PlayerManager::disconnect(const Player::index_t index)
{
	const auto& it = std::find_if(
		s_players.begin(),
		s_players.end(),
		[index](const Player& player) -> bool
		{
			return player.index == index;
		}
	);

	if (it != s_players.end())
	{
		s_recycled_indexes.push(index);
		s_players.erase(it);
	}
}

void PlayerManager::update(const double delta_time)
{
	for (auto& player : s_players)
	{
		if (player.controller == nullptr) continue;

		player.controller->update(delta_time);
	}
}
