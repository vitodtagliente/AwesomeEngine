/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <vdtproto/runtime.h>

#include <awesome/asset/asset.h>
#include <awesome/editor/window.h>

namespace editor
{
	class AssetInspectorWindow : public Window, public IProtoClass
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

		PROTO()

	private:
		std::vector<std::unique_ptr<Inspector>> m_inspectors;
	};
}