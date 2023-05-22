/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <cstddef>
#include <string>

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

	bool open(Settings settings = {});
	void update();
	void close();

	inline void* getHandler() const { return m_handler; }
	inline unsigned int getHeight() const { return static_cast<unsigned int>(m_height); }
	inline unsigned int getWidth() const { return static_cast<unsigned int>(m_width); }
	inline bool isOpen() const { return m_isOpen; }

	void maximize();
	void resize(unsigned int width, unsigned int height);
	void setTitle(const std::string& title);

private:
	void* m_handler{ nullptr };
	int m_width{ 1080 };
	int m_height{ 720 };
	bool m_isOpen{ false };
};