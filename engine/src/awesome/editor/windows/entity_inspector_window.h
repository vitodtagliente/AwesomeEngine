/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

class EntityInspectorWindow : public Window
{
public:
	EntityInspectorWindow();

	virtual char* const getTitle() const override;
	virtual void render() override;

private:
	class EditorState* m_editorState{ nullptr };
};