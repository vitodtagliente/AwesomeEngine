/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/core/timer.h>
#include <awesome/entity/component.h>
#include <vdtmath/vector3.h>

namespace graphics
{
	class Renderer;
}

class world;

struct Wave
{	
	float duration;
	float perMinionSpawnDelay;
	unsigned int numOfMinions;
	math::vec3 spawnPosition;
	std::vector<std::string> pathsToFollow;
	// prefab
};

class WaveManager : public Component
{
public:
	WaveManager();

	void update(double deltatime) override;

	inline bool isActive() const { return m_active; }
	inline const std::vector<Wave>& getWaves() const { return m_waves; }
	inline int getWaveIndex() const { return m_waveIndex; }
	inline bool isCompleted() const { return m_waveIndex >= m_waves.size(); }

	void push(const Wave& wave);
	void start();

private:
	bool m_active;
	std::vector<Wave> m_waves;
	int m_waveIndex;
	Timer m_timer;
};