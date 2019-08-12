#include "shinygalaxy_game.h"

bool ShinyGalaxy::startup_implementation()
{
	m_backgroundColor = Color::Black;

	m_renderer = Renderer::instance();
	m_input = Input::instance();
	m_time = Time::instance();
	m_window = Window::instance();

	m_renderer->enableAlpha();
	// m_renderer->setDrawingMode(Renderer::DrawingMode::Lines);
	// load textures
	if (TextureLibrary * const library = m_renderer->getTextureLibrary())
	{
		library->add("circle", "assets/circle.png");
		library->add("batman", "assets/batman_logo.png");
		library->add("atlas", "assets/texture_atlas.png");
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
	static const float atlas_size = 1.0f / 4.0f;

	m_renderer->clear(m_backgroundColor);

	Texture* const circle_texture = m_renderer->getTextureLibrary()->get("circle");
	Texture* const batman_texture = m_renderer->getTextureLibrary()->get("batman");
	Texture* const atlas_texture = m_renderer->getTextureLibrary()->get("atlas");
	m_renderer->drawTexture(batman_texture, vec2{});
	m_renderer->drawTexture(circle_texture, { .2f, 0.0f }, { .4f, .4f });
	m_renderer->drawRect(Color::Blue, { -.3f, -.3f }, { .2f, .4f });
	m_renderer->drawRect(Color::Red, { .3f, .3f }, 30.0f, { .2f, .4f });
	m_renderer->drawTextureCrop(
		atlas_texture, 
		{ 0.0f, 0.0f, atlas_size, atlas_size }, 
		{ -.3f, -.3f }
	);

	// stress test
	/*
	for (int i = 0; i < 300; ++i)
	{
		m_renderer->drawRect(
			Color(random(0.0f, 1.0f), random(0.0f, 1.0f), random(0.0f, 1.0f)),
			vector2(random(-.8f, .8f), random(-.8f, .8f)),
			random(0.0f, 360.f),
			vector2(random(-.5f, .5f), random(-.5f, .5f))
		);
	}
	*/

	/*
	for (int i = 0; i < 200; ++i)
	{
		m_renderer->drawTexture(
			batman_texture,
			vector2(random(-.8f, .8f), random(-.8f, .8f)),
			random(0.0f, 360.f),
			vector2(random(-.5f, .5f), random(-.5f, .5f))
		);
	}
	*/
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