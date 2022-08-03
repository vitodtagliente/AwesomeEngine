/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>
#include <awesome/editor/window.h>

class Entity;

namespace editor
{
	class SceneWindow : public Window
	{
	public:
		SceneWindow() = default;

		std::string getTitle() const override { return "Scene"; }
		void render() override;

		PROTO()

	private:

		void processInput(Entity* const entity);
		void addEntity();
		void deleteEntity(Entity* const entity);
		void selectEntity(Entity* const entity);
		void renameEntity(Entity* const entity, const std::string& name);

		enum class NavigationState
		{
			Navigating,
			Renaming
		};

		std::string m_filter;
		NavigationState m_state{ NavigationState::Navigating };
		std::string m_tempRename;
	};
}