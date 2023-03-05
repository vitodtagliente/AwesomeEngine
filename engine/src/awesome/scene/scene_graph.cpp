#include "scene_graph.h"

#include <thread>

void SceneGraph::clear()
{
	m_root.removeChildren();
}

bool SceneGraph::load(const SceneAssetPtr& scene)
{
	if (m_state == State::Loading || scene->state != Asset::State::Ready)
	{
		return false;
	}

	clear();
	m_scene = scene;
	m_state = State::Loading;
	std::thread handler([this]()
		{
			for (const Entity& entity : m_scene->data.entities)
			{
				m_root.addChild(std::make_unique<Entity>(entity));
			}
			m_state = State::Ready;
		}
	);
	handler.detach();
	return true;
}

bool SceneGraph::save(const std::filesystem::path& path)
{
	SceneAsset asset;
	for (const auto& entity : m_root.children())
	{
		if (entity->transient) continue;

		asset.data.entities.push_back(*entity);
	}
	return asset.save(path);
}
