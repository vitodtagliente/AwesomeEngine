#include "scene_loader.h"

#include <awesome/application/time.h>
#include <awesome/core/timer.h>

void SceneLoader::load(const SceneAssetPtr& scene, const std::function<void(std::vector<std::unique_ptr<Entity>>&)>& handler)
{
	m_data = json::Deserializer::parse(scene->data);
	const auto& entities = m_data["entities"].as_array({});

	m_handler = handler;
	m_isLoading = true;
	m_progress = 0;
	m_totalProgress = entities.size();
}

void SceneLoader::update(const double)
{
	if (!m_isLoading)
	{
		return;
	}

	Time time;
	const double timeBound = 1.0 / (60 + 20); // 60 fps per second + safety margin

	const auto& entities = m_data["entities"].as_array({});
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
	return (m_totalProgress / 100) * m_progress;
}