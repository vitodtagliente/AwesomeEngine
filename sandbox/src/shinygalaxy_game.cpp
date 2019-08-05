#include "shinygalaxy_game.h"

bool ShinyGalaxy::startup_implementation()
{
	m_backgroundColor = Color::Black;

	m_renderer = Renderer::instance();
	m_input = Input::instance();
	m_time = Time::instance();
	m_window = Window::instance();

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
	static const float speed = 1.5f;
	static float scale_time = .5f;

	if (m_input->isMouseOverWindow())
	{
		const vector2 mouse_position = m_input->getMousePosition();
		const vector3 worldMousePosition = mousePositionToWorld(mouse_position);
		auto diff = worldMousePosition - m_playerPawn->transform.position;

		m_playerPawn->transform.position += diff * speed * deltaTime;
	}

	if (scale_time <= 0.0f)
	{
		const float amount = random(-.01f, .01f);
		float new_size = std::max(0.03f, m_playerPawn->transform.scale.x + amount);
		new_size = std::min(new_size, 0.1f);

		m_playerPawn->transform.scale = { new_size, new_size, 0.0f };
		
		scale_time = .5f;
	}
	scale_time -= deltaTime;
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

vector3 ShinyGalaxy::mousePositionToWorld(const vector2& t_position) const
{
	// #todo manca come mappare il mouse dalla finestra al mondo
	// manca come riottenere le dimensioni della finestra
	return
	{
		t_position.x / m_window->getWidth() * 2 - 1.0f,
		-t_position.y / m_window->getHeight() * 2 + 1.0f,
		0.0f
	};
}