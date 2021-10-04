#include "object_viewer.h"

#include <imgui.h>
#include <awesome/engine/object.h>
#include "../editor.h"
#include "scene_viewer.h"

namespace awesome
{
	ObjectViewer::ObjectViewer()
		: selection()
	{

	}

	ObjectViewer::~ObjectViewer()
	{

	}

	void ObjectViewer::render()
	{
		if (selection != nullptr)
		{
			ImGui::Begin("Object Viewer");
			ImGui::Text(selection->name.data().c_str());
			ImGui::InputFloat3("Position", &selection->transform.position.data[0], 2);
			ImGui::InputFloat3("Rotation", &selection->transform.rotation.data[0], 2);
			ImGui::InputFloat3("Scale", &selection->transform.scale.data[0], 2);
			ImGui::End();
		}
	}
}