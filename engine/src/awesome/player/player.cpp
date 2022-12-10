#include "player.h"

std::vector<Player*> Player::s_instances{};

Player::Player(PlayerIndex index, PlayerController* const controller, PlayerState* const state)
	: m_controller(std::unique_ptr<PlayerController>(controller))
	, m_index(index)
{
	m_controller->m_state = std::unique_ptr<PlayerState>(state);
	s_instances.push_back(this);
}

Player::~Player()
{
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

void Player::init()
{
	m_controller->init();
}

void Player::update(const double deltaTime)
{
	m_controller->update(deltaTime);
}