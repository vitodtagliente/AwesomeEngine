/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/entity/component.h>

#include "../data/wave.h"

#include "spawner_component_generated.h"

CLASS(Category = Component)
class SpawnerComponent : public Component
{
public:
	SpawnerComponent() = default;
	virtual ~SpawnerComponent() = default;

	virtual void init() override;
	virtual void update(double deltaTime);

	virtual void inspect() override;
	
	void start();

	GENERATED_BODY()

private:
	enum class WavePhase
	{
		Beginning,
		Waiting,
		Spawning,
		Ending
	};

	PROPERTY() bool m_autostart{ false };
	bool m_running{ false };
	double m_timer{ 0 };
	int m_waveIndex{ 0 };
	int m_waveInternalIndex{ 0 };
	WavePhase m_wavePhase{ WavePhase::Beginning };
	PROPERTY() std::vector<std::unique_ptr<Wave>> m_waves;
};