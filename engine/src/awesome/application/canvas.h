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
		int width = 1080;
		int height = 720;
		std::string title = "Awesome";
		bool vSync = true;
	};

	Canvas();
	~Canvas() = default;

	bool init();
	bool open(Settings settings = {});
	void update();
	void close();

	int width() const;
	int height() const;

	inline GLFWwindow* getHandler() const { return m_handler; }
	inline bool isOpen() const { return m_isOpen; }

private:

	bool m_isOpen;
	GLFWwindow* m_handler;
};