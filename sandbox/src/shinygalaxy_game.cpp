#include "shinygalaxy_game.h"

bool ShinyGalaxy::startup_implementation()
{
	m_backgroundColor = Color::Black;

	m_renderer = Renderer::instance();
	m_input = Input::instance();
	m_time = Time::instance();

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
}

void ShinyGalaxy::render_implementation()
{
}

void ShinyGalaxy::post_rendering_implementation()
{
}
