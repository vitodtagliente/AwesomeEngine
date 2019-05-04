#include "sandbox_game.h"
#include <iostream>

using namespace std;

bool SandboxGame::startup_imp()
{
	m_input = Input::instance();
	return true;
}

void SandboxGame::shutdown_imp()
{

}

void SandboxGame::update_imp()
{
	if (m_input->isKeyReleased(KeyCode::A))
	{
		cout << "Key Released: A" << endl;
	}
}

/*
SandboxGame::SandboxGame()
	: triangleColor(Color::Black)
{
}

SandboxGame::~SandboxGame()
{
	delete program;
	delete va;
	delete texture;
}

void SandboxGame::init()
{
	Game::init();

	std::map<Shader::Type, std::string> sources;
	Shader::Reader::parse("../../sandbox/assets/texture.shader", sources);
	auto vertex = new Shader(Shader::Type::Vertex, sources[Shader::Type::Vertex]);
	auto fragment = new Shader(Shader::Type::Fragment, sources[Shader::Type::Fragment]);

	if (!vertex->isValid())
	{
		cout << "Vertex " << endl << vertex->getErrorMessage() << endl;
	}
	if (!fragment->isValid())
	{
		cout << "Fragment " << endl << fragment->getErrorMessage() << endl;
	}

	program = new ShaderProgram({ vertex, fragment });
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
	va = new VertexArray();

	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	vb.bind();

	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va->add(vb, layout);

	IndexBuffer ib(indices, 6);
	ib.bind();

	va->unbind();
	vb.unbind();
	ib.unbind();

	Image img("../../sandbox/assets/batman_logo.png");
	texture = new Texture(img.data(), img.getWidth(), img.getHeight(), img.getComponents());
}

void SandboxGame::update(const double delta_time)
{
	Game::update(delta_time);

	if (Input* input = Input::instance())
	{
		if (input->isKeyPressed(KeyCode::A))
		{
			cout << "A down" << endl;
		}
	}

	triangleColor.red += static_cast<float>(delta_time);
	if (triangleColor.red > 1.0f)
		triangleColor.red = 0.0f;
}

void SandboxGame::draw()
{
	static const Color background_color(.15f, .1f, .3f);
	Renderer::instance()->clear(background_color);

	program->bind();
	program->set("u_Color", triangleColor.red, triangleColor.green, triangleColor.green, 1.0f);
	texture->bind();
	program->set("u_Texture", 0);
	va->bind();
	Renderer::instance()->drawElements(6);
}

void SandboxGame::uninit()
{
	Game::uninit();


}

void SandboxGame::end()
{
	Game::end();


}
*/