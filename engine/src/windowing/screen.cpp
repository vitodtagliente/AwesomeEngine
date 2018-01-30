#include <dreamkeeper/windowing/screen.h>

namespace Dreamkeeper
{
	namespace Windowing
	{

		Screen::Screen()
		{

		}

		Screen::Screen(int width, int height)
		{
			resize(width, height);
		}

		Screen::Screen(int width, int height, bool fullscreen)
		{
			setResolution(width, height, fullscreen);
		}

		bool Screen::isFullscreen() const
		{
			return fullscreen;
		}

		int Screen::getWidth() const
		{
			return width;
		}

		int Screen::getHeight() const
		{
			return height;
		}

		void Screen::resize(int width, int height)
		{
			
		}

		void Screen::setResolution(int width, int height, bool fullscreen)
		{

		}

	}
}

