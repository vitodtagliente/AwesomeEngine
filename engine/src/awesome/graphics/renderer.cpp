#include "renderer.h"
#include "graphics_module.h"
#include "render_command.h"

namespace awesome
{
	Renderer::Renderer(GraphicsModule * const t_graphicsModule)
		: m_graphicsModule(t_graphicsModule)
		, m_commandBuffer()
	{
	}
	
	Renderer::~Renderer()
	{
	}

	void Renderer::push(const Mesh& t_mesh)
	{
		push(m_graphicsModule->createRenderable(t_mesh), nullptr);
	}

	void Renderer::push(Renderable* const t_renderable, Material* const t_material, const matrix4& t_transform)
	{
		m_commandBuffer.push_back(RenderCommand(t_renderable, t_material, t_transform));
	}

	void Renderer::render()
	{
		for (const RenderCommand& command : m_commandBuffer.getCommands())
		{
			command.renderable->bind();
			// #todo: make it generic
			drawIndexed(6);
		}

		m_commandBuffer.clear();
	}
}