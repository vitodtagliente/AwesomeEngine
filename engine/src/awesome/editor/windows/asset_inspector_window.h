/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/asset/asset_database.h>
#include <awesome/editor/window.h>

#include "asset_inspector_window_generated.h"

CLASS(Type = Window)
class AssetInspectorWindow : public Window
{
public:
	struct AssetInspector
	{
		AssetInspector() = default;
		virtual ~AssetInspector() = default;
		virtual bool canInspect(const AssetRecord* const /*asset*/) { return false; }
		virtual void update(const AssetRecord* const, double /*deltaTime*/) {}
		virtual void inspect(const AssetRecord* const /*asset*/) = 0;
	};

	AssetInspectorWindow();

	virtual char* const getTitle() const override;
	virtual void init() override;
	virtual void render() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	class EditorState* m_editorState{ nullptr };
	std::vector<std::unique_ptr<AssetInspector>> m_inspectors;
};