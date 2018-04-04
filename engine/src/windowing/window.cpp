#include <awesome/windowing/window.h>

#include <iostream>
#include <awesome/rendering/context.h>
#include <GLFW/glfw3.h>

namespace Awesome
{	
	Window* Window::singleton = nullptr;

	Window::Window()
	{
		window_context = nullptr;
		if (!glfwInit()) {
			std::cout << "Cannot init glfw" << std::endl;
			status == WindowStatus::Error;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		std::cout << "Windowing..." << std::endl;
		window_context = glfwCreateWindow(
			width,
			height,
			title.c_str(), NULL, NULL
		);

		if (!window_context) {
			std::cout << "Cannot create glfw context" << std::endl;
			close();

			status == WindowStatus::Error;
			return;
		}

		glfwMakeContextCurrent(window_context);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Cannot load GLAD" << std::endl;

			status == WindowStatus::Error;
			return;
		}
		else std::cout << "GLAD loaded!" << std::endl;
		glfwSetFramebufferSizeCallback(window_context, framebuffer_size_callback);
	}

	Window::~Window()
	{

	}

	void Window::setTitle(const std::string title)
	{
		this->title = title;
		glfwSetWindowTitle(window_context, title.c_str());
	}

	void Window::resize(int width, int height)
	{
		this->width = width;
		this->height = height;
		glfwSetWindowSize(window_context, width, height);
	}

	void Window::setResolution(int width, int height, bool fullscreen)
	{
		this->width = width;
		this->height = height;
		this->fullscreen = fullscreen;
	}

	void Window::close()
	{
		glfwTerminate();
	}

	void Window::update()
	{
		glfwSwapBuffers(window_context);
		glfwPollEvents();

		application_time = getTime();
	}

	float Window::getTime() const { return glfwGetTime(); }
	float Window::getDeltaTime() const { return getTime() - application_time; }

	bool Window::shouldClose() const { return glfwWindowShouldClose(window_context); }
		
	void Window::resize_callback(GLFWwindow* context, int width, int height)
	{
		glViewport(0, 0, width, height);
		singleton->width = width;
		singleton->height = height;
	}

	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}