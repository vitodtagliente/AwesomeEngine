#pragma once

#include "../editor_view.h"

namespace awesome
{
	class Object;

	class ObjectViewer : public EditorView
	{
	public:

		ObjectViewer();
		~ObjectViewer();

		virtual void render() override;

		// selected object
		Object* selection;
	};
}