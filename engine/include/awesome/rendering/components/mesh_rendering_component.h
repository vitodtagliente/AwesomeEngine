#pragma once

#include "rendering_component.h"

namespace Awesome
{	
	class Mesh;

	class MeshRenderingComponent : public RenderingComponent
	{
	public:
		Mesh* mesh{ nullptr };

		void init() override;
		void update(float delta_time) override;
		void render() override;
	};
}