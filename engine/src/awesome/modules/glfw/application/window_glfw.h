#pragma once

#include <awesome/application/window.h>
#include <awesome/math/vector2.h>

struct GLFWwindow;

namespace awesome
{
	class WindowGLFW final : public Window
	{
	public:

		WindowGLFW();
		 
		virtual void setTitle(const std::string& t_title) override;
		virtual void resize(const uint32 t_width, const uint32 t_height) override;
		inline virtual uint32 getWidth() const override { return m_size.x; }
		inline virtual uint32 getHeight() const override { return m_size.y; }

		inline GLFWwindow* getWindowHandler() const { return m_windowHandler; }

	private:

		// open implementation
		virtual bool open_implementation(const Settings& t_settings) override;
		// close implementation
		virtual void close_implementation() override;

		// module update
		virtual void update_implementation() override;

		// GLFW window handler
		GLFWwindow* m_windowHandler;
		// window size
		vector2_t<uint32> m_size;
	};
}