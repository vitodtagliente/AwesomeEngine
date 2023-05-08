/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>

#include <awesome/asset/scene_asset.h>
#include <awesome/core/singleton.h>

#include "entity.h"
#include "quad_tree.h"

namespace graphics
{
	class Renderer;
}

class SceneGraph final : public Singleton<SceneGraph>
{
public:
	enum class State
	{
		Loading,
		Ready
	};

	SceneGraph() = default;

	inline const QuadTree& quadtree() const { return m_quadtree; }
	Entity& root() { return m_root; }
	inline const SceneAsset& scene() const { return m_scene; }
	inline State state() const { return m_state; }

	void clear();
	void render(graphics::Renderer& renderer);
	void update(double deltaTime);

	bool load(const SceneAsset& scene);
	bool save(const std::filesystem::path& path);

private:
	Entity m_root;
	QuadTree m_quadtree;
	SceneAsset m_scene;
	State m_state{ State::Ready };
};