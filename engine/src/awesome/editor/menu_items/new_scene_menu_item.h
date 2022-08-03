/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtproto/runtime.h>

#include <awesome/editor/menu_item.h>

namespace editor
{
	class NewSceneMenuItem : public MenuItem, public IProtoClass
	{
	public:
		NewSceneMenuItem() = default;
		virtual ~NewSceneMenuItem() = default;

		virtual std::string getCategory() const override { return "Scene"; };
		virtual std::string getName() const override { return "New Scene..."; };

		virtual void execute() override;

		PROTO()
	};
}