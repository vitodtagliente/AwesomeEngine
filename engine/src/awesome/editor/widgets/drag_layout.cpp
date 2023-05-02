#include "drag_layout.h"

#include <imgui.h>

void DragLayout::begin(const char* const name, const char* const item, void* const data, const size_t size)
{
	ImGuiDragDropFlags src_flags = 0;
	src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
	src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
	//src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip
	if (ImGui::BeginDragDropSource(src_flags))
	{
		if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip) && item != nullptr)
			ImGui::Text(item);
		ImGui::SetDragDropPayload(name, data, size);
		ImGui::EndDragDropSource();
	}
}

void DragLayout::end(const char* const name, const std::function<void(void*, size_t)>& handler)
{
	if (ImGui::BeginDragDropTarget())
	{
		ImGuiDragDropFlags target_flags = 0;
		// target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
		// target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(name, target_flags))
		{
			handler(payload->Data, payload->DataSize);
		}
		ImGui::EndDragDropTarget();
	}
}
