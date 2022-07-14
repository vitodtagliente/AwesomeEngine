/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

namespace editor
{
	class EntityInspectorWindow : public Window
	{
	public:
		EntityInspectorWindow() = default;

		std::string getTitle() const override { return "Entity Inspector"; }
		void render() override;

		REFLECT()
	};
}