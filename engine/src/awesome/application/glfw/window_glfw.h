#pragma once

#include "../window.h"

struct GLFWwindow;

namespace awesome
{
	class WindowGLFW final : public Window
	{
	public:

		WindowGLFW();
		 
		virtual void setTitle(const std::string& t_title) override;
		virtual void resize(const uint32 t_width, const uint32 t_height) override;

		inline GLFWwindow* getWindowHandler() const { return m_windowHandler; }

	private:

		// open implementation
		virtual bool open(const Settings& t_settings) override;
		// close implementation
		virtual void close_implementation() override;

		// module update
		virtual void update_implementation() override;

		// GLFW window handler
		GLFWwindow* m_windowHandler;
	};
}