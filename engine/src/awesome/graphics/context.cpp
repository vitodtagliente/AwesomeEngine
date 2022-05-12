#include "context.h"

#include <map>
#include <string>
#include <tuple>
#include <vdtmath/matrix4.h>

#include <glad/glad.h>

#include "index_buffer.h"
#include "vertex_buffer.h"
#include "shader.h"
#include "texture.h"

namespace graphics
{
	Context::Context()
		: projection(math::mat4::identity)
		, view(math::mat4::identity)
		, viewProjectionMatrix(math::mat4::identity)
		, drawCalls(0)
		, m_shaderLibrary()
		, m_textureLibrary()
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
				/*
				 First pixel from memory is bottom-left for OpenGL.
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
				*/
				 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
				-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 1.0f
			};

			unsigned int indices[] = {
				0, 1, 3, 1, 2, 3
			};

			VertexBuffer& vb = *m_spritebatchRenderingData.addVertexBuffer(Renderable::names::MainBuffer, sizeof(vertices), BufferUsageMode::Static);
			vb.fillData(vertices, sizeof(vertices));
			VertexBufferLayout& layout = vb.layout;
			layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
			layout.push(VertexBufferElement("coords", VertexBufferElement::Type::Float, 2));
			IndexBuffer& ib = *m_spritebatchRenderingData.addIndexBuffer(Renderable::names::MainBuffer, sizeof(indices), BufferUsageMode::Static);
			ib.fillData(indices, sizeof(indices));

			VertexBuffer& cropBuffer = *m_spritebatchRenderingData.addVertexBuffer("cropsBuffer", 4 * 2000 * sizeof(float), BufferUsageMode::Stream);
			cropBuffer.layout.push(VertexBufferElement("crop", VertexBufferElement::Type::Float, 4, true, true));
			cropBuffer.layout.startingIndex = 2;

			VertexBuffer& colorBuffer = *m_spritebatchRenderingData.addVertexBuffer("colorsBuffer", 4 * 2000 * sizeof(float), BufferUsageMode::Stream);
			colorBuffer.layout.push(VertexBufferElement("color", VertexBufferElement::Type::Float, 4, true, true));
			colorBuffer.layout.startingIndex = 3;

			VertexBuffer& transformBuffer = *m_spritebatchRenderingData.addVertexBuffer("transformsBuffer", 16 * 2000 * sizeof(float), BufferUsageMode::Stream);
			transformBuffer.layout.push(VertexBufferElement("transform", VertexBufferElement::Type::Float, 4, true, true));
			transformBuffer.layout.push(VertexBufferElement("transform", VertexBufferElement::Type::Float, 4, true, true));
			transformBuffer.layout.push(VertexBufferElement("transform", VertexBufferElement::Type::Float, 4, true, true));
			transformBuffer.layout.push(VertexBufferElement("transform", VertexBufferElement::Type::Float, 4, true, true));
			transformBuffer.layout.startingIndex = 4;

			m_spritebatchRenderingData.bind();
		}
		// texture
		{
			// shaders
			m_textureProgram = createProgram(ShaderLibrary::names::TextureShader);
		}

		// glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Context::clear(const Color& color)
	{
		glClearColor(color.red, color.green, color.blue, color.alpha);
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Context::viewport(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Context::drawLines(const std::vector<std::pair<math::vec3, Color>>& points)
	{
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

		drawLines(vertices);
	}

	void Context::drawLines(const std::vector<float>& vertices)
	{
		if (vertices.empty()) return;

		m_gizmosRenderingData.bind();

		VertexBuffer* vertexBuffer = m_gizmosRenderingData.findVertexBuffer(Renderable::names::MainBuffer);
		vertexBuffer->bind();
		vertexBuffer->fillData((void*)&vertices[0], vertices.size() * sizeof(float));

		m_gizmosProgram->bind();
		m_gizmosProgram->set("u_matrix", viewProjectionMatrix);

		const int primitiveType = GL_LINES;
		const int offset = 0;
		const int count = static_cast<int>(vertices.size() / 7);
		glDrawArrays(primitiveType, offset, count);
		++drawCalls;
	}

	void Context::drawSprites(Texture* const texture, const std::vector<std::tuple<math::mat4, TextureRect, Color>>& sprites)
	{
		// fill geometry data
		std::vector<float> crops;
		std::vector<float> transforms;
		std::vector<float> colors;
		for (auto it = sprites.begin(); it != sprites.end(); ++it)
		{
			const auto& [transform, rect, color] = *it;
			crops.push_back(rect.x);
			crops.push_back(rect.y);
			crops.push_back(rect.width);
			crops.push_back(rect.height);

			transforms.insert(transforms.end(), transform.data, transform.data + transform.length);

			colors.push_back(color.red);
			colors.push_back(color.green);
			colors.push_back(color.blue);
			colors.push_back(color.alpha);
		}

		drawSprites(texture, transforms, crops, colors);
	}

	void Context::drawSprites(Texture* const texture, const std::vector<float>& transforms, const std::vector<float>& crops, const std::vector<float>& colors)
	{
		if (transforms.empty() || crops.empty() || colors.empty()) return;

		const size_t instances = transforms.size() / 16;
		if (instances != crops.size() / 4) return;

		m_spritebatchRenderingData.bind();

		VertexBuffer& cropBuffer = *m_spritebatchRenderingData.findVertexBuffer("cropsBuffer");
		cropBuffer.bind();
		cropBuffer.fillData((void*)&crops[0], crops.size() * sizeof(float));

		VertexBuffer& colorBuffer = *m_spritebatchRenderingData.findVertexBuffer("colorsBuffer");
		colorBuffer.bind();
		colorBuffer.fillData((void*)&colors[0], colors.size() * sizeof(float));

		VertexBuffer& transformBuffer = *m_spritebatchRenderingData.findVertexBuffer("transformsBuffer");
		transformBuffer.bind();
		transformBuffer.fillData((void*)&transforms[0], transforms.size() * sizeof(float));

		m_spritebatchProgram->bind();
		texture->bind(0);
		m_spritebatchProgram->set("u_texture", 0);
		m_spritebatchProgram->set("u_matrix", viewProjectionMatrix);

		const int primitiveType = GL_TRIANGLES;
		const int offset = 0;
		const int count = 6;
		const int numInstances = static_cast<int>(instances);
		const int indexType = GL_UNSIGNED_INT;
		glDrawElementsInstanced(primitiveType, count, indexType, offset, numInstances);
		++drawCalls;
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
			VertexBuffer& vb = *renderable.addVertexBuffer(Renderable::names::MainBuffer, sizeof(vertices), BufferUsageMode::Static);
			vb.fillData(vertices, sizeof(vertices));
			VertexBufferLayout& layout = vb.layout;
			layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
			layout.push(VertexBufferElement("color", VertexBufferElement::Type::Float, 4));
			renderable.bind();

			m_colorProgram->bind();

			glDrawArrays(GL_TRIANGLES, 0, 3);
			++drawCalls;
		}

		// hello line
		if (false)
		{
			float vertices[] = {
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
			};

			Renderable renderable;
			VertexBuffer& vb = *renderable.addVertexBuffer(Renderable::names::MainBuffer, sizeof(vertices), BufferUsageMode::Static);
			vb.fillData(vertices, sizeof(vertices));
			VertexBufferLayout& layout = vb.layout;
			layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
			layout.push(VertexBufferElement("color", VertexBufferElement::Type::Float, 4));
			renderable.bind();

			m_colorProgram->bind();

			glDrawArrays(GL_LINES, 0, 2);
			++drawCalls;
		}

		// hello quad
		if (false)
		{
			float vertices[] = {
				 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
				-1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
			};

			unsigned int indices[] = {
				0, 1, 3, 1, 2, 3
			};

			Renderable renderable;
			renderable.bind();
			VertexBuffer& vb = *renderable.addVertexBuffer(Renderable::names::MainBuffer, sizeof(vertices), BufferUsageMode::Static);
			vb.fillData(vertices, sizeof(vertices));
			VertexBufferLayout& layout = vb.layout;
			layout.push(VertexBufferElement("position", VertexBufferElement::Type::Float, 3));
			layout.push(VertexBufferElement("color", VertexBufferElement::Type::Float, 4));
			vb.activateLayout();
			IndexBuffer& ib = *renderable.addIndexBuffer(Renderable::names::MainBuffer, sizeof(indices), BufferUsageMode::Static);
			ib.fillData(indices, sizeof(indices));

			m_colorProgram->bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			++drawCalls;
		}
	}

	ShaderProgram* const Context::createProgram(const std::string& name)
	{
		std::map<Shader::Type, std::string> sources;
		auto it = m_shaderLibrary.getShaders().find(name);
		if (it != m_shaderLibrary.getShaders().end()
			&& Shader::Reader::parse(it->second, sources))
		{
			Shader vs(Shader::Type::Vertex, sources.find(Shader::Type::Vertex)->second);
			Shader fs(Shader::Type::Fragment, sources.find(Shader::Type::Fragment)->second);
			return new ShaderProgram({ &vs, &fs });
		}
		return nullptr;
	}
}
