#pragma once

#include "../engine/module.h"
#include "index_buffer.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "renderer.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace awesome
{
	class Graphics : public Module<Graphics>
	{
	public:

		enum class API
		{
			Null,
			OpenGL
		};

	protected:

		// module update
		virtual void update_implementation() override;
	};
}