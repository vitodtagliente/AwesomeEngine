/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "window.h"

class Entity;

namespace editor
{
	class Context;

	class SceneTreeWindow : public Window
	{
	public:
		SceneTreeWindow();

		std::string getTitle() const override;
		void render(Context& context) override;

		inline Entity* const getSelectedEntity() const { return m_selectedEntity; }

	private:
		Entity* m_selectedEntity;
	};
}