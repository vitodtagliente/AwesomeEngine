/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/editor/window.h>

class Control;

class UserInterfaceWindow : public Window
{
public:
	UserInterfaceWindow();

	virtual char* const getTitle() const override;
	virtual void render() override;
	virtual void update(double) override;

private:
	void deleteControl(Control* const control);
	void renderControl(Control* const control, Control* const selectedControl);

	class EditorState* m_editorState;
	std::string m_filter;
};