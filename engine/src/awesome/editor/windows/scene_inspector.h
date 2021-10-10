/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/singleton.h>

#include "../window.h"

class Entity;

namespace editor
{
	class Context;

	class SceneInspector : public Window, public Singleton<SceneInspector>
	{
	public:
		SceneInspector();

		std::string getTitle() const override;
		void render(Context& context) override;

		inline Entity* const getSelectedEntity() const { return m_selectedEntity; }

	private:
		Entity* m_selectedEntity;
	};
}