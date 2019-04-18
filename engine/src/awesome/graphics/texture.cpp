#include "texture.h"
#include <glad/glad.h>

namespace awesome
{
	Texture::Options::Options()
		: wrapS(GL_REPEAT)
		, wrapT(GL_REPEAT)
		, filterMin(GL_LINEAR)
		, filterMax(GL_LINEAR)
	{

	}

	Texture::Texture(unsigned char* const t_data, const uint t_width, const uint t_height, const uint t_components, const Options& t_options)
		: m_width(t_width)
		, m_height(t_height)
		, m_format()
	{
		// generate the texture
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		/* set the texture wrapping/filtering options (on the currently bound texture object) */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, t_options.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_options.wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, t_options.filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, t_options.filterMax);

		if (t_data) 
		{
			if (t_components == 1)
				m_format = GL_RED;
			else if (t_components == 3)
				m_format = GL_RGB;
			else if (t_components == 4)
				m_format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, m_format, t_width, t_height,
				0, m_format, GL_UNSIGNED_BYTE, t_data
			);
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	uint Texture::id() const
	{
		return m_id;
	}

	void Texture::bind(const uint t_slot)
	{
		glActiveTexture(GL_TEXTURE0 + t_slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint Texture::getWidth() const
	{
		return m_width;
	}

	uint Texture::getHeight() const
	{
		return m_height;
	}
}