#include "context.h"

#include <map>
#include <string>
#include <glad/glad.h>
#include "shader.h"
#include <vdtmath/matrix4.h>

Context::Context()
	: camera(math::mat4::identity)
	, m_shaderLibrary()
	, m_gizmosRenderingData()
	, m_spritebatchRenderingData()
	, m_gizmosProgram()
	, m_colorProgram()
	, m_spritebatchProgram()
{
	// color
	{
		// shaders
		m_colorProgram = createProgram(ShaderLibrary::names::ColorShader);
	}
	// gizmos
	{
		// shaders
		m_gizmosProgram = createProgram(ShaderLibrary::names::GizmosShader);

		// render data
		VertexBuffer& vb = *m_gizmosRenderingData.addVertexBuffer(Renderable::names::MainBuffer, 7 * 2000 * sizeof(float), BufferUsageMode::Static);
		VertexBufferLayout& layout = vb.layout;
		layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
		layout.push(VertexBufferElement("color", VertexBufferElement::Type::Float, 4));
	}
	// spritebatch
	{
		// shaders
		m_spritebatchProgram = createProgram(ShaderLibrary::names::SpriteBatchShader);

		float vertices[] = {
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 3, 1, 2, 3
		};

		// render data
		VertexBuffer& vb = *m_spritebatchRenderingData.addVertexBuffer(Renderable::names::MainBuffer, 20 * sizeof(float), BufferUsageMode::Static);
		VertexBufferLayout& layout = vb.layout;
		layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
		layout.push(VertexBufferElement("textcoords", VertexBufferElement::Type::Float, 2));
		vb.fillData(vertices, 20 * sizeof(float));

		IndexBuffer& ib = *m_spritebatchRenderingData.addIndexBuffer(Renderable::names::MainBuffer, 6 * sizeof(unsigned int), BufferUsageMode::Static);
		ib.fillData(indices, 6 * sizeof(unsigned int));

		VertexBuffer& cropBuffer = *m_spritebatchRenderingData.addVertexBuffer("cropsBuffer", 4 * 2000 * sizeof(float), BufferUsageMode::Static);
		cropBuffer.layout.push(VertexBufferElement("crop", VertexBufferElement::Type::Float, 4, true, true));
		cropBuffer.layout.startingIndex = 2;

		VertexBuffer& transformBuffer = *m_spritebatchRenderingData.addVertexBuffer("transformsBuffer", 16 * 2000 * sizeof(float), BufferUsageMode::Static);
		transformBuffer.layout.push(VertexBufferElement("transform", VertexBufferElement::Type::Float, 4, true, true));
		transformBuffer.layout.push(VertexBufferElement("transform", VertexBufferElement::Type::Float, 4, true, true));
		transformBuffer.layout.push(VertexBufferElement("transform", VertexBufferElement::Type::Float, 4, true, true));
		transformBuffer.layout.push(VertexBufferElement("transform", VertexBufferElement::Type::Float, 4, true, true));
		transformBuffer.layout.startingIndex = 3;
	}
}

void Context::clear(const Color& color)
{
	glClearColor(color.red, color.green, color.blue, color.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Context::viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Context::drawLines(const std::vector<std::pair<math::vec3, Color>>& points)
{
	if (points.empty()) return;

	m_gizmosRenderingData.bind();

	// fill geometry data
	std::vector<float> vertices;
	for (auto it = points.begin(); it != points.end(); ++it)
	{
		vertices.push_back(it->first.x);
		vertices.push_back(it->first.y);
		vertices.push_back(it->first.z);
		vertices.push_back(it->second.red);
		vertices.push_back(it->second.green);
		vertices.push_back(it->second.blue);
		vertices.push_back(it->second.alpha);
	}

	VertexBuffer* vertexBuffer = m_gizmosRenderingData.findVertexBuffer(Renderable::names::MainBuffer);
	vertexBuffer->bind();
	vertexBuffer->fillData(&vertices[0], vertices.size() * sizeof(float));

	m_gizmosProgram->bind();
	m_gizmosProgram->set("u_matrix", camera);

	const int primitiveType = GL_LINES;
	const int offset = 0;
	const int count = points.size();
	glDrawArrays(primitiveType, offset, count);
}

void Context::drawSprites(Texture* const texture, const std::vector<std::pair<math::transform, TextureRect>>& sprites)
{
	if (sprites.empty()) return;

	m_spritebatchRenderingData.bind();

	// fill geometry data
	std::vector<float> crops;
	std::vector<float> transforms;
	for (auto it = sprites.begin(); it != sprites.end(); ++it)
	{
		crops.push_back(it->second.x);
		crops.push_back(it->second.y);
		crops.push_back(it->second.width);
		crops.push_back(it->second.height);

		for (int i = 0; i < 16; ++i)
		{
			transforms.push_back(it->first.matrix().data[i]);
		}
	}

	VertexBuffer& cropBuffer = *m_spritebatchRenderingData.findVertexBuffer("cropsBuffer");
	cropBuffer.bind();
	cropBuffer.fillData(&crops[0], crops.size() * sizeof(float));

	VertexBuffer& transformBuffer = *m_spritebatchRenderingData.findVertexBuffer("transformsBuffer");
	transformBuffer.bind();
	transformBuffer.fillData(&transforms[0], transforms.size() * sizeof(float));

	m_gizmosProgram->bind();
	texture->bind(0);
	m_gizmosProgram->set("u_texture", 0);
	m_gizmosProgram->set("u_matrix", camera);

	const int primitiveType = GL_TRIANGLES;
	const int offset = 0;
	const int count = 6;
	const int numInstances = sprites.size();
	const int indexType = GL_UNSIGNED_SHORT;
	glDrawElementsInstanced(primitiveType, count, indexType, offset, numInstances);
}

void Context::test()
{
	// hello triangle
	if (false)
	{
		float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		Renderable renderable;
		VertexBuffer& vb = *renderable.addVertexBuffer(Renderable::names::MainBuffer, 21 * sizeof(float), BufferUsageMode::Static);
		vb.fillData(vertices, 21 * sizeof(float));
		VertexBufferLayout& layout = vb.layout;
		layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
		layout.push(VertexBufferElement("color", VertexBufferElement::Type::Float, 4));
		renderable.bind();

		m_colorProgram->bind();

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	// hello line
	if (false)
	{
		float vertices[] = {
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		Renderable renderable;
		VertexBuffer& vb = *renderable.addVertexBuffer(Renderable::names::MainBuffer, 12 * sizeof(float), BufferUsageMode::Static);
		vb.fillData(vertices, 21 * sizeof(float));
		VertexBufferLayout& layout = vb.layout;
		layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
		layout.push(VertexBufferElement("color", VertexBufferElement::Type::Float, 4));
		renderable.bind();

		m_colorProgram->bind();

		glDrawArrays(GL_LINES, 0, 2);
	}
}

ShaderProgram* const Context::createProgram(const std::string& name)
{
	std::map<Shader::Type, std::string> sources;
	auto it = m_shaderLibrary.getShaders().find(name);
	if (it != m_shaderLibrary.getShaders().end()
		&& Shader::Reader::parse(it->second, sources));
	{
		Shader vs(Shader::Type::Vertex, sources.find(Shader::Type::Vertex)->second);
		Shader fs(Shader::Type::Fragment, sources.find(Shader::Type::Fragment)->second);
		return new ShaderProgram({ &vs, &fs });
	}
	return nullptr;
}
