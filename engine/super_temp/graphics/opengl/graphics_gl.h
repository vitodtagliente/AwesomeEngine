#pragma once

#include "../graphics.h"
#include "index_buffer_gl.h"
#include "shader_gl.h"
#include "shader_program_gl.h"
#include "texture_gl.h"
#include "renderer_gl.h"
#include "vertex_array_gl.h"
#include "vertex_buffer_gl.h"
#include "vertex_buffer_layout_gl.h"

namespace awesome
{
	class GraphicsGL final : public Graphics
	{
	private:

		// module startup
		virtual bool startup_implementation() override;

		// module update
		virtual void update_implementation() override;
	};
}