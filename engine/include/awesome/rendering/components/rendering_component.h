#pragma once

#include "../../component.h"
#include "../shading/material.h"

namespace Awesome
{
	class RenderingComponent : public Component
	{
	public:
		Material* material{ nullptr };

		virtual void render();
	};
}