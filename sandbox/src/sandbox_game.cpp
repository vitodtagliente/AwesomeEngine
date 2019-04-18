#include "sandbox_game.h"
#include <iostream>

using namespace std;

SandboxGame::SandboxGame()
	: triangleColor(Color::Black)
{
}

SandboxGame::~SandboxGame()
{
	delete program;
	delete va;
}

void SandboxGame::init()
{
	Game::init();

	std::map<Shader::Type, std::string> sources;
	Shader::Reader::parse("../../sandbox/assets/triangle.shader", sources);
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

	// position_x position_y 
	float positions[] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	// Vertex Array
	va = new VertexArray();

	VertexBuffer vb(positions, 2 * 3 * sizeof(float));
	vb.bind();

	VertexBufferLayout layout;
	layout.push<float>(2);

	va->add(vb, layout);

	va->unbind();
	vb.unbind();
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
	va->bind();
	Renderer::instance()->draw();
}

void SandboxGame::uninit()
{
	Game::uninit();


}

void SandboxGame::end()
{
	Game::end();


}