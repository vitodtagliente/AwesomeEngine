#include "wave_manager.h"

#include <future>

#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/sprite_renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <vdtmath/algorithm.h>

#include "minion.h"

WaveManager::WaveManager()
	: Component()
	, m_active(false)
	, m_waves()
	, m_waveIndex(-1)
	, m_timer(0)
{
}

void WaveManager::update(double deltatime)
{
	if (m_active)
	{
		m_timer.tick(deltatime);
		if (m_timer.isExpired())
		{
			++m_waveIndex;
			if (m_waveIndex < m_waves.size())
			{
				const Wave& nextWave = m_waves[m_waveIndex];
				m_timer.configure(nextWave.duration);
				std::async([world = getWorld(), nextWave]() 
					{
						for (int i = 0; i < nextWave.numOfMinions; ++i)
						{
							Entity* const entity = world->spawn(math::vec3(math::random(-12.f, -2.f), 0.f, 0.f), math::quaternion::identity);
							entity->name = std::string("minion");
							entity->tag = "minion";
							entity->addComponent<Minion>();
							if (SpriteRenderer* component = entity->addComponent<SpriteRenderer>())
							{
								const float spriteSize = 1.0f / 11;
								component->texture = graphics::TextureLibrary::instance()->get("sheet");
								component->rect = graphics::TextureRect(spriteSize * 9, spriteSize * 4, spriteSize, spriteSize);
							}
							if (GizmosRenderer* component = entity->addComponent<GizmosRenderer>())
							{
								component->type = GizmosRenderer::Type::Rect;
							}
						}
					}
				);
			}
		}
	}
}

void WaveManager::push(const Wave& wave)
{
	m_waves.push_back(wave);
}

void WaveManager::start()
{
	m_active = true;
}
