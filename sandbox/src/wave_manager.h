/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include <awesome/core/timer.h>
#include <awesome/scene/component.h>
#include <vdtmath/vector3.h>

namespace editor
{
	class Context;
}

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

	void update(World& world, double deltatime) override;
	void inspect(editor::Context& context) override;

	inline bool isActive() const { return m_active; }
	inline const std::vector<Wave>& getWaves() const { return m_waves; }
	inline int getWaveIndex() const { return m_waveIndex; }
	inline bool isCompleted() const { return m_waveIndex >= m_waves.size(); }

	void push(const Wave& wave);
	void start();

private:
	void spawnWave(World& world, const Wave& wave);

	bool m_active;
	std::vector<Wave> m_waves;
	int m_waveIndex;
	Timer m_timer;
};