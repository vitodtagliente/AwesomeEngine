#include "canvas.h"

#include <SDL3/SDL.h>

#include "input.h"
#include "keycode.h"

Canvas::~Canvas()
{
	if (SDL_Window* const handler = reinterpret_cast<SDL_Window*>(m_handler))
	{
		SDL_DestroyWindow(handler);
		SDL_Quit();
	}
}

bool Canvas::open(Settings settings)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("SDL_Init failed (%s)", SDL_GetError());
		return false;
	}

	SDL_Window* handler = SDL_CreateWindow(
		settings.title.c_str(),
		settings.width,
		settings.height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
	);

	if (handler == nullptr)
	{
		SDL_Log("SDL_CreateWindow failed (%s)", SDL_GetError());
		return false;
	}

	m_handler = reinterpret_cast<void*>(handler);
	m_width = settings.width;
	m_height = settings.height;
	m_isOpen = true;

	return true;
}

void Canvas::update()
{
	if (SDL_Window* const handler = reinterpret_cast<SDL_Window*>(m_handler))
	{
		SDL_GetWindowSize(handler, &m_width, &m_height);
	}

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT: m_isOpen = false; break;
		case SDL_EVENT_KEY_DOWN: Input::instance().setKeyState(event.key.keysym.sym, KeyState::Down); break;
		case SDL_EVENT_KEY_UP: Input::instance().setKeyState(event.key.keysym.sym, KeyState::Released); break;
		case SDL_EVENT_MOUSE_MOTION: 
			Input::instance().setMousePosition(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN: Input::instance().setKeyState(event.button.button, KeyState::Down); break;
		case SDL_EVENT_MOUSE_BUTTON_UP:Input::instance().setKeyState(event.button.button, KeyState::Released); break;
		case SDL_EVENT_MOUSE_WHEEL:
			Input::instance().setMouseWheelPosition(static_cast<float>(event.wheel.x), static_cast<float>(event.wheel.y));
			break;
		}
	}
}

void Canvas::close()
{
	m_isOpen = false;
}

void Canvas::wait(const std::size_t ms)
{
	SDL_Delay(static_cast<Uint32>(ms));
}

void Canvas::maximize()
{
	if (SDL_Window* const handler = reinterpret_cast<SDL_Window*>(m_handler))
	{
		SDL_MaximizeWindow(handler);
	}
}

void Canvas::resize(unsigned int width, unsigned int height)
{
	if (SDL_Window* const handler = reinterpret_cast<SDL_Window*>(m_handler))
	{
		SDL_SetWindowSize(handler, static_cast<int>(width), static_cast<int>(height));
	}
}

void Canvas::setTitle(const std::string& title)
{
	if (SDL_Window* const handler = reinterpret_cast<SDL_Window*>(m_handler))
	{
		SDL_SetWindowTitle(handler, title.c_str());
	}
}