#include "spawner_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/color.h>

void SpawnerComponent::init()
{
	m_running = m_autostart;
}

void SpawnerComponent::update(const double deltaTime)
{
	if (!m_running
		|| m_waves.empty()
		|| m_waveIndex >= m_waves.size())
	{
		return;
	}

	m_timer -= deltaTime;
	if (m_timer < 0)
	{
		switch (m_wavePhase)
		{
		case WavePhase::Beginning:
		{
			m_timer = m_waves[m_waveIndex]->startSpawnDelay;
			m_waveInternalIndex = 0;
			m_wavePhase = WavePhase::Waiting;
			break;
		}
		case WavePhase::Waiting:
		{
			m_wavePhase = WavePhase::Spawning;
			break;
		}
		case WavePhase::Spawning:
		{
			const auto& currentWave = m_waves[m_waveIndex];
			if (currentWave->minionPrefab == nullptr
				|| !currentWave->minionPrefab->data.has_value())
			{
				break;
			}

			if (m_waveInternalIndex++ >= currentWave->quantity)
			{
				m_wavePhase = WavePhase::Ending;
				break;
			}

			math::vec3 spawnPosition = currentWave->spawnPosition;
			if (currentWave->spawnType == SpawnType::AroundPosition)
			{
				spawnPosition.x += math::random(-currentWave->spawnRange.x, currentWave->spawnRange.x);
				spawnPosition.y = math::random(-currentWave->spawnRange.y, currentWave->spawnRange.y);
			}
			World::instance().addChild(currentWave->minionPrefab, spawnPosition);
			m_timer = currentWave->perSpawnDelay;
			break;
		}
		case WavePhase::Ending:
		{
			++m_waveIndex;
			m_wavePhase = WavePhase::Beginning;
			break;
		}
		default: break;
		}
	}
}

void SpawnerComponent::inspect()
{
	Component::inspect();
	if (Layout::button("Start", graphics::Color(0.f, .6f, .6f)))
	{
		start();
	}
}

void SpawnerComponent::start()
{
	m_running = true;
	m_waveIndex = 0;
	m_wavePhase = WavePhase::Beginning;
}
