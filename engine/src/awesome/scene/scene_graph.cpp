#include "scene_graph.h"

#include <thread>

void SceneGraph::update(const double deltaTime)
{
	m_quadtree.clear(math::vec3::zero, {10.f, 10.f});
	m_root.update(m_quadtree, deltaTime);
}

void SceneGraph::clear()
{
	m_root.removeChildren();
}

bool SceneGraph::load(const SceneAsset& scene)
{
	if (m_state == State::Loading || scene.state != Asset::State::Ready)
	{
		return false;
	}

	clear();
	m_scene = scene;
	m_state = State::Loading;
	std::thread handler([this]()
		{
			for (const Entity& entity : m_scene.resource->entities)
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
	Scene scene;
	for (const auto& entity : m_root.children())
	{
		if (entity->transient) continue;

		scene.entities.push_back(*entity);
	}
	return ResourcerWriter<Scene>::write(scene, path);
}
