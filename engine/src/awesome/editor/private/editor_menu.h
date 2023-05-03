/// Copyright (c) Vito Domenico Tagliente
#pragma once

class EditorMenu
{
public:
	EditorMenu();

	void init();
	void render();

private:
	void menuAssets();
	void menuFile();
	void menuScene();
	void menuView();

	class EditorState* m_editorState;
};