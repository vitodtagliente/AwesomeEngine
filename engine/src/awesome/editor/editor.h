/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <queue>
#include <vector>

#include <awesome/application/application.h>
#include <awesome/asset/asset.h>
#include <awesome/core/event.h>

#include "editor_settings.h"
#include "private/menu.h"
#include "window.h"

namespace graphics
{
	class Renderer2D;
}

class Editor : public Application::Module, public Singleton<Editor>
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

		void select();
		void select(const AssetPtr& asset);
		void select(class Entity* const entity);
		void select(const std::filesystem::path& path);

		std::filesystem::path path;
		Selection selection;

		// events
		event onSelectedAssetChanged;
		event onSelectedEntityChanged;
		event onSelectedPathChanged;

	private:
		std::queue<AssetPtr> history;
	};

	Editor() = default;

	virtual void startup() override;
	virtual void shutdown() override;
	virtual void preRendering() override;
	virtual void render(graphics::Renderer2D* const renderer) override;
	virtual void postRendering() override;
	virtual void update(double deltaTime) override;

	template <typename T = Window>
	void registerWindow()
	{
		m_windows.push_back(std::make_unique<T>());
	}

	EditorSettings settings;
	State state;

private:
	void registerWindows();

	Menu m_menu;
	std::vector<std::unique_ptr<Window>> m_windows;
};