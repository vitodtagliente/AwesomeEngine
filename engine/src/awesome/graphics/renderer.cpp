#include "renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../data/color.h"

namespace awesome
{
	void Renderer::clear(const Color& t_color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(t_color.red, t_color.green, t_color.blue, t_color.alpha);
	}

	void Renderer::draw(const unsigned int t_vertices)
	{
		glDrawArrays(GL_TRIANGLES, 0, t_vertices);
	}
	
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::init()
	{
		if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
	}

	void Renderer::uninit()
	{
	}
}