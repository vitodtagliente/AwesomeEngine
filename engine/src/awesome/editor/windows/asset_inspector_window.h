/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/asset/asset_database.h>
#include <awesome/editor/asset_inspector.h>
#include <awesome/editor/window.h>

class AssetInspectorWindow : public Window
{
public:
	AssetInspectorWindow();

	virtual char* const getTitle() const override;

	virtual void init() override;
	virtual void render() override;
	virtual void update(double deltaTime) override;

private:
	class EditorState* m_editorState{ nullptr };
	std::vector<std::unique_ptr<AssetInspector>> m_inspectors;
};