#include "texture.h"

#include <glad/glad.h>

namespace graphics
{
	Texture::Options::Options()
		: wrapS(GL_REPEAT)
		, wrapT(GL_REPEAT)
		, filterMin(GL_LINEAR)
		, filterMax(GL_LINEAR)
	{

	}

	Texture::Texture(const unsigned char* const data, const unsigned int width, const unsigned int height,
		const unsigned int channels, const Options& options /* = Options */)
		: m_id()
		, m_width(width)
		, m_height(height)
		, m_format(channels)
	{
		// generate the texture
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		/* set the texture wrapping/filtering options (on the currently bound texture object) */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options.wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options.filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options.filterMax);

		if (data)
		{
			if (channels == 1)
				m_format = GL_RED;
			else if (channels == 3)
				m_format = GL_RGB;
			else if (channels == 4)
				m_format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, m_format, width, height,
				0, m_format, GL_UNSIGNED_BYTE, data
			);
		}
	}

	Texture::~Texture()
	{
		free();
	}

	void Texture::bind(const unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::free()
	{
		glDeleteTextures(1, &m_id);
	}
}