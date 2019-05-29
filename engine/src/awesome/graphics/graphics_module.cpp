#include "graphics_module.h"

#include <vector>

namespace awesome
{
	GraphicsModule::GraphicsModule(const API t_api)
		: m_api(t_api)
	{
	}

	GraphicsModule::~GraphicsModule()
	{
	}
	
	Renderable* GraphicsModule::createRenderable(const Mesh& t_mesh)
	{
		std::vector<float> vertex_data;
		for (int i = 0; i < t_mesh.positions.size(); ++i)
		{
			const vector3& position = t_mesh.positions[i];
			vertex_data.push_back(position.x);
			vertex_data.push_back(position.y);
			vertex_data.push_back(position.z);

			if (t_mesh.uv.size() > 0)
			{
				const vector2& uv = t_mesh.uv[i];
				vertex_data.push_back(uv.x);
				vertex_data.push_back(uv.y);
			}
		}

		GraphicsBuffer * const vb = createBuffer(
			GraphicsBuffer::Type::Vertex, 
			vertex_data.data(), 
			vertex_data.size() * sizeof(float)
		);

		vb->layout.push({ 3, GraphicsBufferElement::Type::Float, sizeof(float) });
		vb->layout.push({ 2, GraphicsBufferElement::Type::Float, sizeof(float) });

		GraphicsBuffer* const ib = createBuffer(
			GraphicsBuffer::Type::Index, 
			t_mesh.indices.data(), 
			t_mesh.indices.size() * sizeof(unsigned int)
		);

		Renderable* const renderable = createRenderable(vb, ib);

		

		delete vb;
		delete ib;

		return renderable;
	}

	bool GraphicsModule::startup_implementation()
	{
		return false;
	}
	
	void GraphicsModule::shutdown_implementation()
	{
	}
	
	void GraphicsModule::update_implementation()
	{
	}
}