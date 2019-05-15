#include "sandbox_game.h"
#include <iostream>

using namespace std;

// #todo
#include <awesome/graphics/opengl/vertex_array_gl.h>
#include <awesome/graphics/opengl/index_buffer_gl.h>
#include <awesome/graphics/opengl/vertex_buffer_layout_gl.h>
#include <awesome/graphics/opengl/vertex_buffer_gl.h>

bool SandboxGame::startup_implementation()
{
	// set the background color
	m_color = { .2f, .2f, .2f };

	if (GraphicsModule * const graphics = GraphicsModule::instance())
	{
		std::map<Shader::Type, std::string> sources;
		Shader::Reader::parse("assets/texture.shader", sources);
		auto vertex = graphics->createShader(Shader::Type::Vertex, sources[Shader::Type::Vertex]);
		auto fragment = graphics->createShader(Shader::Type::Fragment, sources[Shader::Type::Fragment]);

		cout << "Vertex " << endl;
		cout << ((vertex->isValid()) ? sources[Shader::Type::Vertex] : vertex->getErrorMessage()) << endl;

		cout << "Fragment " << endl;
		cout << ((fragment->isValid()) ? sources[Shader::Type::Fragment] : fragment->getErrorMessage()) << endl;

		m_program = graphics->createShaderProgram({ vertex, fragment });
		if (!m_program->isValid())
		{
			cout << "Program " << endl << m_program->getErrorMessage() << endl;
		}

		// free shaders
		delete vertex;
		delete fragment;

		Image img("assets/batman_logo.png");
		m_texture = graphics->createTexture(img.data(), img.getWidth(), img.getHeight(), img.getComponents());

		// position_x position_y uv_x uv_y
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 1.0f, 0.0f,
			0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		// #todo: to be incapsulated
		// Vertex Array
		m_va = new VertexArrayGL();

		VertexBuffer* vb = new VertexBufferGL(positions, 4 * 4 * sizeof(float));
		vb->bind();

		VertexBufferLayout* layout = new VertexBufferLayoutGL();
		layout->push<float>(2);
		layout->push<float>(2);
		m_va->add(vb, layout);

		IndexBuffer* ib = new IndexBufferGL(indices, 6);
		ib->bind();

		m_va->unbind();
		vb->unbind();
		ib->unbind();

		delete vb;
		delete ib;

		Renderer::instance()->enableAlpha();

		return true;
	}
	return false;
}

void SandboxGame::shutdown_implementation()
{
	delete m_program;
	delete m_texture;
	delete m_va;
}

void SandboxGame::update_implementation()
{
	// update
	const double deltaTime = Time::instance()->getDeltaTime();
	Input* const input = Input::instance();

	// update
	if (input->isKeyReleased(KeyCode::A))
	{
		cout << "Key Released: A" << endl;
	}

	m_triangleColor.red += static_cast<float>(deltaTime);
	if (m_triangleColor.red > 1.0f)
		m_triangleColor.red = 0.0f;

	// render
	if (Renderer * renderer = Renderer::instance())
	{
		renderer->clear(m_color);

		m_program->bind();
		m_program->set("u_Color", m_triangleColor.red, m_triangleColor.green, m_triangleColor.green, 1.0f);
		m_texture->bind();
		m_program->set("u_Texture", 0);
		m_va->bind();
		renderer->drawIndexed(6);
	}
}