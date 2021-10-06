#include "context.h"

#include <map>
#include <string>
#include <glad/glad.h>
#include "shader.h"
#include <vdtmath/matrix4.h>

Context::Context()
	: m_shaderLibrary()
	, m_gizmosRenderingData(7 * 2000, 0, BufferUsageMode::Stream)
	, m_gizmosProgram()
{
	// gizmos
	{
		// shaders
		std::map<Shader::Type, std::string> sources;
		auto shaderIt = m_shaderLibrary.getShaders().find(ShaderLibrary::names::GizmosShader);
		if (Shader::Reader::parse(shaderIt->second, sources));
		{
			Shader vs(Shader::Type::Vertex, sources.find(Shader::Type::Vertex)->second);
			Shader fs(Shader::Type::Fragment, sources.find(Shader::Type::Fragment)->second);
			m_gizmosProgram = new ShaderProgram({ &vs, &fs });
		}

		// render data
		VertexBufferLayout& layout = m_gizmosRenderingData.getVertexBuffer().layout;
		layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
		layout.push(VertexBufferElement("color", VertexBufferElement::Type::Float, 4));
	}
}

void Context::clear(const Color& color)
{
	glClearColor(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	glClear(GL_COLOR_BUFFER_BIT);
}

void Context::viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Context::drawLines(const std::vector<std::pair<math::vec3, Color>>& lines)
{
	if (lines.empty()) return;

	m_gizmosRenderingData.bind();

	// fill geometry data
	std::vector<float> vertices;
	for (auto it = lines.begin(); it != lines.end(); ++it)
	{
		vertices.push_back(it->first.x);
		vertices.push_back(it->first.y);
		vertices.push_back(it->first.z);
		vertices.push_back(it->second.getRed());
		vertices.push_back(it->second.getGreen());
		vertices.push_back(it->second.getBlue());
		vertices.push_back(it->second.getAlpha());
	}

	VertexBuffer& vertexBuffer = m_gizmosRenderingData.getVertexBuffer();
	vertexBuffer.bind();
	vertexBuffer.fillData(&vertices[0], vertices.size());

	m_gizmosProgram->bind();
	m_gizmosProgram->set("u_matrix", math::mat4::identity.data[0]); // camera

	const int primitiveType = GL_LINES;
	const int offset = 0;
	const int count = lines.size();
	glDrawArrays(primitiveType, offset, count);
}
