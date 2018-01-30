#pragma once

namespace Dreamkeeper
{
	namespace Windowing
	{
		class Screen
		{
		private:
			int width = 640;
			int height = 480;
			bool fullscreen = false;

		public:
			Screen();
			Screen(int width, int height);
			Screen(int width, int height, bool fullscreen);

			bool isFullscreen() const;
			int getWidth() const;
			int getHeight() const;

			void resize(int width, int height);
			void setResolution(int width, int height, bool fullscreen);
		};
	}
}