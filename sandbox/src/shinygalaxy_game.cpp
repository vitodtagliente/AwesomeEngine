#include "shinygalaxy_game.h"

bool ShinyGalaxy::startup_implementation()
{
	m_backgroundColor = Color::Black;

	m_renderer = Renderer::instance();
	m_input = Input::instance();
	m_time = Time::instance();

	GraphicsAPI* api = m_renderer->getAPI();

	std::map<Shader::Type, std::string> sources;
	Shader::Reader::parse("assets/projection.shader", sources);
	auto vertex = api->createShader(Shader::Type::Vertex, sources[Shader::Type::Vertex]);
	auto fragment = api->createShader(Shader::Type::Fragment, sources[Shader::Type::Fragment]);
	auto m_program = api->createShaderProgram({ vertex, fragment });

	// free shaders
	delete vertex;
	delete fragment;

	m_renderer->enableAlpha();
	Texture* const texture = m_renderer->getTextureLibrary()->add("circle", "assets/circle.png");

	// sprite material initialization
	m_spriteMaterial = new Material(m_program);
	m_spriteMaterial->set("u_Texture", texture);

	// #todo: errori con lo scale?
	m_playerPawn = createCircle({}, {.05f, .1f, 0.0f});



	return true;
}

void ShinyGalaxy::shutdown_implementation()
{
}

void ShinyGalaxy::update_implementation()
{
	const double deltaTime = m_time->getDeltaTime();

	m_playerPawn->transform.position =
		(getMousePosition());
}

void ShinyGalaxy::pre_rendering_implementation()
{
	m_renderer->clear(m_backgroundColor);
}

void ShinyGalaxy::render_implementation()
{
}

void ShinyGalaxy::post_rendering_implementation()
{
}

Object* ShinyGalaxy::createCircle(const vector3& t_position, const vector3& t_scale) const
{
	static int i = 0;

	auto m_sprite = spawn();
	m_sprite->name = "Sprite " + std::to_string(i); ++i;
	m_sprite->transform.position = t_position;
	m_sprite->transform.scale = t_scale;
	SpriteComponent* const sprite_component = m_sprite->addComponent<SpriteComponent>();
	sprite_component->material = m_spriteMaterial;
	return m_sprite;
}

vector3 ShinyGalaxy::getMousePosition() const
{
	const vec2 m_position = m_input->getMousePosition();
	// #todo manca come mappare il mouse dalla finestra al mondo
	// manca come riottenere le dimensioni della finestra
	return
	{
		m_position.x / 640.0f,
		-m_position.y / 480.0f,
		0.0f
	};
}
