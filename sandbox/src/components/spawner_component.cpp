#include "spawner_component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

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
			m_timer = m_waves[m_waveIndex].startSpawnDelay;
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
			const Wave& currentWave = m_waves[m_waveIndex];
			if (currentWave.minionPrefab == nullptr
				|| !currentWave.minionPrefab->data.has_value())
			{
				break;
			}

			if (m_waveInternalIndex++ >= currentWave.quantity)
			{
				m_wavePhase = WavePhase::Ending;
				break;
			}

			math::vec3 spawnPosition = currentWave.spawnPosition;
			if (currentWave.spawnType == SpawnType::AroundPosition)
			{
				spawnPosition.x += math::random(-currentWave.spawnRange.x, currentWave.spawnRange.x);
				spawnPosition.y = math::random(-currentWave.spawnRange.y, currentWave.spawnRange.y);
			}
			World::instance().spawn(currentWave.minionPrefab, spawnPosition);
			m_timer = currentWave.perSpawnDelay;
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

json::value SpawnerComponent::serialize() const
{
	json::value data = Component::serialize();
	json::value waves = json::array();
	for (const Wave& wave : m_waves)
	{
		json::value waveData = Serializer::serialize(wave);
		waveData["spawnType"] = enumToString(wave.spawnType);
		waves.push_back(waveData);
	}
	data["waves"] = waves;
	return data;
}

void SpawnerComponent::deserialize(const json::value& value)
{
	Component::deserialize(value);
	const auto& wavesData = value.safeAt("waves").as_array({});
	for (const json::value& waveData : wavesData)
	{
		Wave wave;
		Deserializer::deserialize(waveData, wave);
		stringToEnum(waveData.safeAt("spawnType").as_string(""), wave.spawnType);
		m_waves.push_back(wave);
	}
}

void SpawnerComponent::inspect()
{
	Component::inspect();
	// Layout::input(m_waves);
	Layout::separator();
	if (Layout::button("Start"))
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
