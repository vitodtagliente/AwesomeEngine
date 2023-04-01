/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>

#include <awesome/asset/scene_asset.h>
#include <awesome/core/singleton.h>

#include "entity.h"

class SceneGraph final : public Singleton<SceneGraph>
{
public:
	enum class State
	{
		Loading,
		Ready
	};

	SceneGraph() = default;

	Entity* const root() { return &m_root; }

	void clear();

	bool load(const std::shared_ptr<SceneAsset>& scene);
	inline const std::shared_ptr<SceneAsset>& scene() const { return m_scene; }
	bool save(const std::filesystem::path& path);
	inline State state() const { return m_state; }

private:
	Entity m_root;
	std::shared_ptr<SceneAsset> m_scene;
	State m_state{ State::Ready };
};