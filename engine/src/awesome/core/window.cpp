#include <awesome/core/window.h>

namespace awesome
{
	Window::Window(const std::string& title, const WindowProperties& properties)
	{
		m_Title = title;
		m_Properties = properties;
	}

	Window::~Window()
	{
		// unregister this window
		for (auto it = m_Windows.begin(); it != m_Windows.end(); ++it) {
			if (it->second == this) {
				m_Windows.erase(it);
				break;
			}
		}

		// delete the input manager
		delete m_InputManager;
	}
	
	void Window::enableVSync(const bool enabled) {
		m_Properties.vSync = enabled;
		// TODO
	}

	void Window::setFPS(const uint8 fps) {
		if (fps > 0)
		{
			m_Properties.fps = fps;
			m_TimePerFrame = 1.0f / fps;
		}
	}

	void Window::clear() {
		// TODO
	}

	void Window::update() {
		platformUpdate();

		// update the input manager
		if (m_InputManager)
			m_InputManager->update();
	}

	void Window::open() {
		if (m_State != WindowState::Created)
			return;
		
		if (platformOpen())
		{
			m_State = WindowState::Open;

			// initialize the input manager
			m_InputManager = new InputManager();
			m_InputManager->init(m_WindowHandler);

			// register this window
			m_Windows.insert(std::pair<void* const, Window* const>{m_WindowHandler, this});

			// FPS 
			setFPS(m_Properties.fps);
		}
		else
		{
			m_State = WindowState::Error;
		}
	}

	void Window::close() {
		if (m_State != WindowState::Open)
			return;

		m_State = WindowState::Closing;
	}

	// store and find all windows
	std::map<void* const, Window* const> Window::m_Windows{};

	Window* Window::instance(void* const window_handler) {
		const auto it = m_Windows.find(window_handler);
		if (it != m_Windows.end()) {
			return it->second;
		}
		return nullptr;
	}
}