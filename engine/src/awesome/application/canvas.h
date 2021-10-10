/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <cstddef>
#include <string>

#include <GLFW/glfw3.h>

#include <awesome/core/singleton.h>

class Canvas : public Singleton<Canvas>
{
public:

	struct Settings
	{
		unsigned int width = 1080;
		unsigned int height = 720;
		std::string title = "Awesome";
		bool vSync = true;
	};

	Canvas();
	~Canvas() = default;

	bool open(Settings settings = {});
	void update();
	void close();

	inline GLFWwindow* getHandler() const { return m_handler; }
	unsigned int getWidth() const { return m_width; }
	unsigned int getHeight() const { return m_height; }
	inline bool isOpen() const { return m_isOpen; }

private:
	static void handleResize(GLFWwindow*, const int width, const int height);

	GLFWwindow* m_handler;
	unsigned int m_width;
	unsigned int m_height;
	bool m_isOpen;
};