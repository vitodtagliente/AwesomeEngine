#include "object_viewer.h"

#include <imgui.h>
#include <awesome/scene/object.h>
#include <awesome/editor/editor.h>
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
			ImGui::InputFloat3("Position", &selection->transform.position.data[0], 2);
			ImGui::InputFloat3("Rotation", &selection->transform.rotation.data[0], 2);
			ImGui::InputFloat3("Scale", &selection->transform.scale.data[0], 2);
			ImGui::End();
		}
	}
}