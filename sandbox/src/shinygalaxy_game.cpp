#include "shinygalaxy_game.h"

bool ShinyGalaxy::startup_implementation()
{
	m_backgroundColor = Color::Black;

	m_renderer = Renderer::instance();
	m_input = Input::instance();
	m_time = Time::instance();
	m_window = Window::instance();

	m_renderer->enableAlpha();
	// load textures
	if (TextureLibrary * const library = m_renderer->getTextureLibrary())
	{
		library->add("circle", "assets/circle.png");
		library->add("batman", "assets/batman_logo.png");
	}

	return true;
}

void ShinyGalaxy::shutdown_implementation()
{
}

void ShinyGalaxy::update_implementation()
{
	const double deltaTime = m_time->getDeltaTime();
}

void ShinyGalaxy::pre_rendering_implementation()
{
	m_renderer->clear(m_backgroundColor);

	Texture* const circle_texture = m_renderer->getTextureLibrary()->get("circle");
	Texture* const batman_texture = m_renderer->getTextureLibrary()->get("batman");
	//m_renderer->drawTexture(batman_texture, vec2{});
	m_renderer->drawRect(Color::Blue, { -.3f, -.3f }, { .2f, .4f });
	m_renderer->drawRect(Color::Blue, { .3f, .3f }, { .2f, .4f });
}

void ShinyGalaxy::render_implementation()
{
}

void ShinyGalaxy::post_rendering_implementation()
{
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