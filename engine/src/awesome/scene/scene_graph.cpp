#include "scene_graph.h"

#include <thread>

#include <awesome/graphics/renderer.h>

SceneGraph::SceneGraph()
{
	m_root.name = "root";
}

void SceneGraph::clear()
{
	m_root.removeChildren();
}

void SceneGraph::flush()
{
	m_root.flush();
}

void SceneGraph::render(graphics::Renderer& renderer)
{
	m_root.render(renderer);
}

void SceneGraph::update(const double deltaTime)
{
	m_root.update(deltaTime);
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
	//std::thread handler([this]()
		{
			for (const Entity& entity : m_scene.resource->entities)
			{
				m_root.addChild(std::make_unique<Entity>(entity));
			}
			m_state = State::Ready;
		}
	//);
	//handler.detach();
	return true;
}

bool SceneGraph::save(const std::filesystem::path& path)
{
	Scene scene;
	for (const auto& entity : m_root.children())
	{
		if (entity->transient) continue;

		Entity persistEntity(*entity);
		scene.entities.push_back(std::move(persistEntity));
	}
	return ResourcerWriter<Scene>::write(scene, path);
}
