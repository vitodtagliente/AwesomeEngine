#include "scene_viewer.h"

#include <awesome/scene/world.h>

namespace awesome
{
	SceneViewer::SceneViewer()
		: m_world()
	{
	}
	
	SceneViewer::~SceneViewer()
	{
	}

	void SceneViewer::init()
	{
		m_world = World::instance();
	}

	void SceneViewer::render()
	{
		if (m_world)
		{

		}
	}

	void SceneViewer::uninit()
	{
	}
}