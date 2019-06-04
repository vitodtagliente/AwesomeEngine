#include "sandbox_game.h"
#include <iostream>

using namespace std;

bool SandboxGame::startup_implementation()
{
	// set the background color
	m_color = { .2f, .2f, .2f };

	// projection matrix
	m_projection = mat4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	// view matrix
	m_view = mat4::identity;

	if (GraphicsModule * const graphics = GraphicsModule::instance())
	{
		std::map<Shader::Type, std::string> sources;
		Shader::Reader::parse("assets/projection.shader", sources);
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

		m_renderer = Renderer::instance();
		m_renderer->enableAlpha();

		// generate the quad renderable
		m_quad = graphics->createRenderable(Quad{});

		// sprite material initialization
		m_spriteMaterial = new Material(m_program);
		m_spriteMaterial->set("u_Texture", m_texture);

		// objects tests
		World* const world = World::instance();
		m_sprite = world->spawn();
		m_sprite->transform.scale = { 0.5f, 0.5f, 1.0f };
		SpriteComponent* const sprite_component = m_sprite->addComponent<SpriteComponent>();

		// tests

		m_transform1.scale = { 0.5f, 0.5f, 1.0f };
		//m_transform1.rotation.z = 20.0f;
		m_transform1.update();

		return true;
	}
	return false;
}

void SandboxGame::shutdown_implementation()
{
	delete m_program;
	delete m_texture;
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
}

void SandboxGame::pre_rendering_implementation()
{
	m_renderer->clear(m_color);
}

void SandboxGame::render_implementation()
{
	m_renderer->push(m_quad, m_spriteMaterial, m_projection * m_view * m_transform1.matrix());

	// ... push other data

	m_renderer->render();
}

void SandboxGame::post_rendering_implementation()
{

}
