#pragma once

#include <dreamkeeper/core/interfaces/base_element.h>
#include <glad/glad.h>
#include <string>

namespace Dreamkeeper
{
	namespace Shading
	{
		class Texture : public Core::BaseElement
		{
		private:
			int width{ 0 }, height{ 0 };

		public:
			GLuint internalFormat{ GL_RGBA }; // Format of texture object
			GLuint imageFormat{ GL_RGBA }; // Format of loaded image
			GLuint wrapS{ GL_REPEAT }; // Wrapping mode on S axis
			GLuint wrapT{ GL_REPEAT }; // Wrapping mode on T axis
			GLuint filterMin{ GL_LINEAR }; // Filtering mode if texture pixels < screen pixels
			GLuint filterMax{ GL_LINEAR }; // Filtering mode if texture pixels > screen pixels

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