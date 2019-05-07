#include "sandbox_game.h"
#include <iostream>
#include <awesome/graphics/opengl/graphics_gl.h>

using namespace std;

bool SandboxGame::startup_implementation()
{
	m_input = Input::instance();

	triangleColor = Color::Black;

	renderer = new RendererGL();

	std::map<Shader::Type, std::string> sources;
	Shader::Reader::parse("assets/texture.shader", sources);
	auto vertex = new ShaderGL(Shader::Type::Vertex, sources[Shader::Type::Vertex]);
	auto fragment = new ShaderGL(Shader::Type::Fragment, sources[Shader::Type::Fragment]);

	if (!vertex->isValid())
	{
		cout << "Vertex " << endl << vertex->getErrorMessage() << endl;
	}
	if (!fragment->isValid())
	{
		cout << "Fragment " << endl << fragment->getErrorMessage() << endl;
	}

	program = new ShaderProgramGL({ vertex, fragment });
	if (!program->isValid())
	{
		cout << "Program " << endl << program->getErrorMessage() << endl;
	}

	// free shaders
	delete vertex;
	delete fragment;

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

	// Vertex Array
	va = new VertexArrayGL();

	VertexBuffer* vb = new VertexBufferGL(positions, 4 * 4 * sizeof(float));
	vb->bind();

	VertexBufferLayout* layout = new VertexBufferLayoutGL();
	layout->push<float>(2);
	layout->push<float>(2);
	va->add(vb, layout);

	IndexBuffer* ib = new IndexBufferGL(indices, 6);
	ib->bind();

	va->unbind();
	vb->unbind();
	ib->unbind();

	delete vb;
	delete ib;

	Image img("assets/batman_logo.png");
	texture = new TextureGL(img.data(), img.getWidth(), img.getHeight(), img.getComponents());

	return true;
}

void SandboxGame::shutdown_implementation()
{
	delete program;
	delete va;
	delete texture;
}

void SandboxGame::update_implementation()
{
	// update
	if (m_input->isKeyReleased(KeyCode::A))
	{
		cout << "Key Released: A" << endl;
	}

	triangleColor.red += static_cast<float>(Time::instance()->getDeltaTime());
	if (triangleColor.red > 1.0f)
		triangleColor.red = 0.0f;

	// draw
	static const Color background_color(.15f, .1f, .3f);
	renderer->clear(background_color);

	program->bind();
	program->set("u_Color", triangleColor.red, triangleColor.green, triangleColor.green, 1.0f);
	texture->bind();
	program->set("u_Texture", 0);
	va->bind();
	renderer->drawIndexed(6);
}