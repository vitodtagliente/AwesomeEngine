#include "canvas.h"

Canvas::Canvas()
	: m_isOpen(false)
	, m_handler()
{
}

bool Canvas::init()
{
	if (glfwInit())
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// return gladLoadGL();
		return true;
	}
	return false;
}

bool Canvas::open(Settings settings)
{
	m_handler = glfwCreateWindow(
		settings.width,
		settings.height,
		settings.title.c_str(),
		false,
		false
	);

	if (m_handler != nullptr)
	{
		glfwMakeContextCurrent(m_handler);

		// resize callback
		glfwSetFramebufferSizeCallback(
			m_handler,
			[](GLFWwindow*, int width, int height)
			{
				// if (WindowGLFW* const window = static_cast<WindowGLFW*>(Window::instance()))
				// {
				// 	window->m_size = {
				// 		static_cast<uint32>(t_width),
				// 		static_cast<uint32>(t_height)
				// 	};
				// }
				// // #todo
				// if (Renderer* const renderer = Renderer::instance())
				// {
				// 	renderer->setViewport(t_width, t_height);
				// }
			}
		);
		m_isOpen = true;
		return true;
	}
	return false;
}

void Canvas::update()
{
	glfwPollEvents();

	// check for closing window
	if (glfwWindowShouldClose(m_handler))
	{
		m_isOpen = false;
	}
	glfwSwapBuffers(m_handler);
}

void Canvas::close()
{
}
