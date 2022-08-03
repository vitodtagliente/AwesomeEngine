/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtproto/runtime.h>

#include <awesome/editor/menu_item.h>

namespace editor
{
	class SpriteAnimationMenuItem : public MenuItem, public IProtoClass
	{
	public:
		SpriteAnimationMenuItem() = default;
		virtual ~SpriteAnimationMenuItem() = default;

		virtual std::string getCategory() const override { return "Assets"; };
		virtual std::string getName() const override { return "Sprite Animation"; };

		virtual void execute() override;

		PROTO()
	};
}