#pragma once

#include "../window.h"

namespace awesome
{
	class GLFWWindow final : public Window
	{
	public:

		GLFWWindow();
		virtual ~GLFWWindow() override;

		virtual bool open(const Settings& t_settings) override;
		virtual void update() override;
		 
		virtual void setTitle(const std::string& t_title) override;
		virtual void resize(const uint32 t_width, const uint32 t_height) override;

	private:

		// GLFW window handler
		struct ::GLFWwindow* m_windowHandler;
	};
}