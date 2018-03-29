#include <awesome/rendering/shading/texture.h>
#include <awesome/rendering/context.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Awesome
{
	Texture::Texture()
	{
		internalFormat = imageFormat = GL_RGBA;
		wrapS = wrapT = GL_REPEAT;
		filterMin = filterMax = GL_LINEAR;
	}

	Texture::Texture(unsigned int format)
	{
		internalFormat = imageFormat = format;
		wrapS = wrapT = GL_REPEAT;
		filterMin = filterMax = GL_LINEAR;
	}

	bool Texture::load(std::string filename)
	{
		if (id == 0)
			glGenTextures(1, &id);

		bind();

		/* set the texture wrapping/filtering options (on the currently bound texture object) */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

		/* load image data from file */
		int numComponents = 0;
		unsigned char* data;
		data = stbi_load(filename.c_str(), &width, &height, &numComponents, 0);
		if (data) {
			if (numComponents == 1)
				this->imageFormat = GL_RED;
			else if (numComponents == 3)
				this->imageFormat = GL_RGB;
			else if (numComponents == 4)
				this->imageFormat = GL_RGBA;
			this->internalFormat = this->imageFormat;

			glTexImage2D(
				GL_TEXTURE_2D, 0, this->internalFormat,
				width, height, 0, this->imageFormat,
				GL_UNSIGNED_BYTE, data
			);
			glGenerateMipmap(GL_TEXTURE_2D);
				
			unbind();
			/* free the image memory */
			stbi_image_free(data);
			return true;
		}
		unbind();
		return false;
	}

	int Texture::getWidth() const
	{
		return width;
	}

	int Texture::getHeight() const
	{
		return height;
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::free()
	{
		glDeleteTextures(1, &id);
	}
}