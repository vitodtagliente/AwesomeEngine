#include "player.h"

#include <awesome/entity/world.h>

#include "player_controller.h"
#include "player_state.h"

const std::string Player::EntityTag{ "Player" };
std::vector<Player*> Player::s_instances{};

void Player::prepareToSpawn()
{
	Entity::prepareToSpawn();
	m_controller = findComponent<PlayerController>(); 
	s_instances.push_back(this);
}

Player* const Player::initialize(const PlayerIndex index, const std::string& controller, const std::string& state)
{
	Player* player = getPlayer(index);
	if (player != nullptr)
	{
		return player;
	}

	player = new Player();
	player->name = "Player[" + std::to_string(static_cast<int>(index)) + "]";
	player->tag = Player::EntityTag;
	player->m_index = index;
	player->persistent = true;
	player->transform.isStatic = true;
	player->transient = true;
	player->addComponent(TypeFactory::instantiate<PlayerState>(state));
	player->addComponent(TypeFactory::instantiate<PlayerController>(controller));
	World::instance().spawn(player);

	return player;
}

void Player::prepareToDestroy()
{
	Entity::prepareToDestroy();
	const auto& it = std::find_if(s_instances.begin(), s_instances.end(), [index = m_index](Player* const player) -> bool
		{
			return player->getIndex() == index;
		}
	);
	s_instances.erase(it);
}

Player* const Player::getPlayer(const PlayerIndex index)
{
	const auto& it = std::find_if(s_instances.begin(), s_instances.end(), [index](Player* const player) -> bool
		{
			return player->getIndex() == index;
		}
	);

	if (it != s_instances.end())
	{
		return *it;
	}
	return nullptr;
}