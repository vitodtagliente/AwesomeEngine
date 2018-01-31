#pragma once

#include <string>

namespace Awesome
{
	namespace Rendering
	{
		class Texture
		{
		private:
			
			int width{ 0 }, height{ 0 };

		public:

			unsigned int id{ 0 };

			/* Format of texture object */
			unsigned int internalFormat;
			/* Format of loaded image */
			unsigned int imageFormat;
			/* Wrapping mode on S axis */
			unsigned int wrapS; 
			/* Wrapping mode on T axis */
			unsigned int wrapT; 
			/* Filtering mode if texture pixels < screen pixels */
			unsigned int filterMin; 
			/* Filtering mode if texture pixels > screen pixels */
			unsigned int filterMax; 

			Texture();
			Texture(unsigned int format);

			bool load(std::string filename);

			int getWidth() const;
			int getHeight() const;

			void bind();
			void unbind();
			void free();
		};
	}
}