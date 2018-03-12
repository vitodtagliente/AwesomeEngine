#pragma once

#include <string>

class GLFWwindow;

namespace Awesome
{
	class Application;

	namespace Windowing
	{
		enum WindowStatus
		{
			Created,
			Closing,
			Closed,
			Error
		};

		class Window
		{
		private:
			static Window* singleton;

			int width = 640;
			int height = 480;
			bool fullscreen = false;
			std::string title{"AwesomeEngine"};

			float application_time{ 0.0f };

			WindowStatus status{ WindowStatus::Created };

			/* GLFW context */
			GLFWwindow* window_context{ nullptr };
			
			static void resize_callback(GLFWwindow* context, int width, int height);
			static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

			Window();
			~Window();

		public:
			template <class T>
			static Window* open()
			{
				if (singleton == nullptr)
				{
					T* t_window = new T{};
					singleton = dynamic_cast<Window*>(t_window);
				}
				return singleton;
			}

			static Window* instance() { return singleton; }	

			WindowStatus getStatus() const { return status; }

			bool isFullscreen() const { return fullscreen; }
			int getWidth() const { return width; }
			int getHeight() const { return height; }

			void setTitle(const std::string title);
			void resize(int width, int height);
			void setResolution(int width, int height, bool fullscreen);

			float getTime() const;

			void update();
			bool shouldClose() const;

			void close();
		};
	}
}