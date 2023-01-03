/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <queue>
#include <vector>

#include <awesome/application/application_module.h>
#include <awesome/asset/asset.h>
#include <awesome/core/event.h>

#include "editor_settings.h"
#include "private/menu.h"
#include "window.h"

namespace graphics
{
	class Renderer2D;
}

class World;

class Editor : public ApplicationModule
{
public:
	class State
	{
	public:
		struct Selection
		{
			AssetPtr asset;
			class Entity* entity{ nullptr };
		};

		void select(const AssetPtr& asset);
		void select(class Entity* const entity);
		void select(const std::filesystem::path& path);
		void unselectAsset();
		void unselectEntity();

		std::filesystem::path path;
		Selection selection;

		// events
		event_t<AssetPtr> onSelectedAssetChanged;
		event_t<Entity*> onSelectedEntityChanged;
		event_t<std::filesystem::path> onSelectedPathChanged;

	private:
		std::queue<AssetPtr> m_history;
	};

	Editor();

	virtual void startup() override;
	virtual void shutdown() override;
	virtual void preRendering() override;
	virtual void render(World* const, graphics::Renderer2D* const renderer) override;
	virtual void postRendering() override;
	virtual void update(double deltaTime) override;

	static Editor* const instance() { return s_instance; }

	template <typename T = Window>
	void registerWindow()
	{
		m_windows.push_back(std::make_unique<T>());
	}

	const std::vector<std::unique_ptr<Window>>& getWindows() const { return m_windows; }

	EditorSettings settings;
	State state;

private:
	void registerWindows();

	static Editor* s_instance;

	Menu m_menu;
	std::vector<std::unique_ptr<Window>> m_windows;
};