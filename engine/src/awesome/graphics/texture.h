/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

namespace graphics
{
	class Texture
	{
	public:
		struct Options
		{
			Options();

			// Wrapping mode on S axis
			unsigned int wrapS;
			// Wrapping mode on T axis 
			unsigned int wrapT;
			// Filtering mode if texture pixels < screen pixels
			unsigned int filterMin;
			// Filtering mode if texture pixels > screen pixels
			unsigned int filterMax;
		};

		Texture(const unsigned char* const data, unsigned int width, unsigned int height,
			unsigned int channels, const Options& options = Options{});
		~Texture();

		inline unsigned int id() const { return m_id; }
		inline bool isValid() const { return m_id != 0; }

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }

		void bind(unsigned int slot = 0);
		void unbind();
		void free();

	protected:

		// texture id
		unsigned int m_id;
		// texture size
		unsigned int m_width, m_height;
		// format of the texture object
		unsigned int m_format;
	};

	typedef std::shared_ptr<Texture> TexturePtr;
}