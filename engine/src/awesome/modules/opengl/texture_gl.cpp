#include "texture_gl.h"

#include "opengl.h"

namespace awesome
{
	Texture::Options::Options()
		: wrapS(GL_REPEAT)
		, wrapT(GL_REPEAT)
		, filterMin(GL_LINEAR)
		, filterMax(GL_LINEAR)
	{

	}

	TextureGL::TextureGL(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height,
		const unsigned int t_channels, const Options& t_options /* = Options */)
		: Texture(t_data, t_width, t_height, t_channels, t_options)
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
			if (t_channels == 1)
				m_format = GL_RED;
			else if (t_channels == 3)
				m_format = GL_RGB;
			else if (t_channels == 4)
				m_format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, m_format, t_width, t_height,
				0, m_format, GL_UNSIGNED_BYTE, t_data
			);
		}
	}

	TextureGL::~TextureGL()
	{
		glDeleteTextures(1, &m_id);
	}

	void TextureGL::bind()
	{
		bind(0);
	}

	void TextureGL::bind(const unsigned int t_slot)
	{
		glActiveTexture(GL_TEXTURE0 + t_slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void TextureGL::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}