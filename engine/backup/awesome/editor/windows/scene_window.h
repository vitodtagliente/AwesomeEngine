/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

#include "scene_window_generated.h"

class Entity;

CLASS(Type = Window)
class SceneWindow : public Window
{
public:
	SceneWindow() = default;

	virtual std::string getTitle() const override;
	virtual void render() override;
	virtual void update(double) override;

	GENERATED_BODY()

private:
	void addEntity(const std::string& type, Entity* const parent);
	void deleteEntity(Entity* const entity);
	void renderEntity(Entity* const entity, Entity* const selectedEntity);
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