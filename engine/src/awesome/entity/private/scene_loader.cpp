#include "scene_loader.h"

#include <awesome/application/time.h>
#include <awesome/core/timer.h>
#include <awesome/encoding/json.h>

void SceneLoader::load(const SceneAssetPtr& asset, const std::function<void(std::vector<std::unique_ptr<Entity>>&)>& handler)
{
	m_asset = asset;
	m_handler = handler;
	m_isLoading = true;
	m_progress = 0;
	m_totalProgress = asset->data.value()["entities"].as_array({}).size();
}

void SceneLoader::update(const double)
{
	if (!m_isLoading)
	{
		return;
	}

	Time time;
	const double timeBound = 1.0 / 30; // 60 fps per second + safety margin

	const auto& entities = m_asset->data.value()["entities"].as_array({});
	while (time.getTime() < timeBound && m_progress < m_totalProgress)
	{
		const json::value& data = entities.at(m_progress);
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		entity->deserialize(data);
		m_entities.push_back(std::move(entity));
		++m_progress;

		time.tick();
	}

	if (m_progress == m_totalProgress)
	{
		m_isLoading = false;
		m_handler(m_entities);
	}
}

bool SceneLoader::isLoading() const
{
	return m_isLoading;
}

size_t SceneLoader::getProgress() const
{
	return static_cast<size_t>((100.0 / m_totalProgress) * m_progress);
}