/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/editor/window.h>

class Entity;

class SceneWindow : public Window
{
public:
	SceneWindow();

	virtual char* const getTitle() const override;
	virtual void render() override;
	virtual void update(double) override;

private:
	void deleteEntity(Entity* const entity);
	void renderEntity(Entity* const entity, Entity* const selectedEntity);

	class EditorState* m_editorState;
	std::string m_filter;
};