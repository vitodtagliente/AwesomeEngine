/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

#include "buffer.h"

namespace graphics
{
	class IndexBuffer;
	class VertexBuffer;

	class Renderable
	{
	public:

		Renderable();
		~Renderable();

		void bind(bool forceBinding = false);
		void unbind();
		void free();

		IndexBuffer* const findIndexBuffer(const std::string& name);
		VertexBuffer* const findVertexBuffer(const std::string& name);

		IndexBuffer* const addIndexBuffer(const std::string& name, size_t size, BufferUsageMode usageMode);
		VertexBuffer* const addVertexBuffer(const std::string& name, size_t size, BufferUsageMode usageMode);

		struct names
		{
			names() = delete;

			static const std::string MainBuffer;
		};

	private:

		// vertex array object
		unsigned int m_id;
		std::map<std::string, VertexBuffer*> m_vertexBuffers;
		std::map<std::string, IndexBuffer*> m_indexBuffers;
		bool m_binded;
	};
}