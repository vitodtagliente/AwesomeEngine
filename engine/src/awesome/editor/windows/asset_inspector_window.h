/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/asset/asset.h>
#include <awesome/editor/window.h>

#include "asset_inspector_window_generated.h"

CLASS(Category = Window)
class AssetInspectorWindow : public Window
{
public:

	struct Inspector
	{
		Inspector() = default;
		virtual ~Inspector() = default;
		virtual bool canInspect(const AssetPtr& /*asset*/) { return false; }
		virtual void update(const AssetPtr&, double /*deltaTime*/) {}
		virtual void inspect(const AssetPtr& /*asset*/) = 0;
	};

	AssetInspectorWindow() = default;

	virtual std::string getTitle() const override { return "Asset Inspector"; }
	virtual void init() override;
	virtual void render() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	std::vector<std::unique_ptr<Inspector>> m_inspectors;
};