#pragma once

#include "../window.h"

struct GLFWwindow;

namespace awesome
{
	class WindowGLFW final : public Window
	{
	public:

		WindowGLFW();
		
		virtual bool open(const Settings& t_settings) override;
		virtual void close() override;
		 
		virtual void setTitle(const std::string& t_title) override;
		virtual void resize(const uint32 t_width, const uint32 t_height) override;

		inline GLFWwindow* getWindowHandler() const { return m_windowHandler; }

	private:

		// module update
		virtual void update_imp() override;

		// GLFW window handler
		GLFWwindow* m_windowHandler;
	};
}