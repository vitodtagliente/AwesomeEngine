#pragma once

#include "../../scenegraph/component.h"

namespace Awesome
{	
	namespace Rendering
	{
		class Mesh;

		class MeshRenderingComponent : public Scenegraph::Component
		{
		public:
			Mesh* mesh{ nullptr };

			void init() override;
			void update(float delta_time) override;
		};
	}
}