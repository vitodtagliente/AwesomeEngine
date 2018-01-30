#include <awesome/awesome.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Awesome
{

	int execute_main(Application* app)
	{
		// TOOD: device type check
		return desktop_device_main(app);
	}

	int desktop_device_main(Application* app)
	{
		GLFWwindow* window = nullptr;
		if (!glfwInit()) {
			std::cout << "Cannot init glfw" << std::endl;
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		

		std::cout << "Windowing..." << std::endl;
		window = glfwCreateWindow(
			//app->screen.getWidth(),
			//app->screen.getHeight(),
			640, 
			480,
			"DreamkeeperEngine app", NULL, NULL
		);
		if (!window) {
			std::cout << "Cannot create glfw context" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		if (/*!gladLoadGL()*/!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Cannot load GLAD" << std::endl;
			return -1;
		}
		else std::cout << "GLAD loaded!" << std::endl;
		//glfwSetFramebufferSizeCallback(window, handle_resize);

		app->init();

		while (!glfwWindowShouldClose(window) && app->isRunning()) {
			glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			app->update(glfwGetTime());
			app->render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		};

		glfwTerminate();
		return 0;
	}

	int mobile_device_main(Application* app)
	{
		return 0;
	}

}