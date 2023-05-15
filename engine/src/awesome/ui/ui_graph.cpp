#include "ui_graph.h"

#include <thread>

void UIGraph::clear()
{
	m_root.removeChildren();
}

void UIGraph::update(const double deltaTime)
{
	m_root.update(deltaTime);
}

bool UIGraph::load(const UserInterfaceAsset& ui)
{
	if (m_state == State::Loading || ui.state != Asset::State::Ready)
	{
		return false;
	}

	clear();
	m_ui = ui;
	m_state = State::Loading;
	std::thread handler([this]()
		{
			for (const Control& control : m_ui.resource->controls)
			{
				m_root.addChild(std::make_unique<Control>(control));
			}
			m_state = State::Ready;
		}
	);
	handler.detach();
	return true;
}

bool UIGraph::save(const std::filesystem::path& path)
{
	UserInterface ui;
	for (const auto& control : m_root.children())
	{
		ui.controls.push_back(*control);
	}
	return ResourcerWriter<UserInterface>::write(ui, path);
}
