#include "renderable.h"

#include <glad/glad.h>

#include "index_buffer.h"
#include "vertex_buffer.h"

namespace graphics
{
	Renderable::Renderable()
		: m_id()
		, m_vertexBuffers()
		, m_indexBuffers()
		, m_binded(false)
	{
		glGenVertexArrays(1, &m_id);
	}

	Renderable::~Renderable()
	{
		free();
	}

	void Renderable::bind(const bool forceBinding)
	{
		glBindVertexArray(m_id);
		if (!m_binded || forceBinding)
		{
			for (auto& pair : m_vertexBuffers)
			{
				pair.second->bind();
				pair.second->activateLayout();
			}
			for (auto& pair : m_indexBuffers)
			{
				pair.second->bind();
			}
			m_binded = true;
		}
	}

	void Renderable::unbind()
	{
		glBindVertexArray(0);
	}

	void Renderable::free()
	{
		glDeleteVertexArrays(1, &m_id);
		for (auto& pair : m_vertexBuffers)
		{
			pair.second->free();
			delete pair.second;
		}
		m_vertexBuffers.clear();

		for (auto& pair : m_indexBuffers)
		{
			pair.second->free();
			delete pair.second;
		}
		m_indexBuffers.clear();
	}

	IndexBuffer* const Renderable::findIndexBuffer(const std::string& name)
	{
		const auto& it = m_indexBuffers.find(name);
		return it != m_indexBuffers.end() ? it->second : nullptr;
	}

	VertexBuffer* const Renderable::findVertexBuffer(const std::string& name)
	{
		const auto& it = m_vertexBuffers.find(name);
		return it != m_vertexBuffers.end() ? it->second : nullptr;
	}

	IndexBuffer* const Renderable::addIndexBuffer(const std::string& name, const size_t size, const BufferUsageMode usageMode)
	{
		IndexBuffer* buffer = new IndexBuffer(size, usageMode);
		const auto& it = m_indexBuffers.insert(std::make_pair(name, buffer));
		return it.first->second;
	}

	VertexBuffer* const Renderable::addVertexBuffer(const std::string& name, const size_t size, const BufferUsageMode usageMode)
	{
		VertexBuffer* buffer = new VertexBuffer(size, usageMode);
		const auto& it = m_vertexBuffers.insert(std::make_pair(name, buffer));
		return it.first->second;
	}

	const std::string Renderable::names::MainBuffer = "main";
}