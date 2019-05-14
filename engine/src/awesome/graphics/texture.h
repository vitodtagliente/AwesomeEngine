#pragma once

namespace awesome
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

		Texture(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height,
			const unsigned int t_components, const Options& t_options = Options{});

		inline unsigned int id() const { return m_id; }
		inline bool isValid() const { return m_id != 0; }

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }

		virtual void bind() = 0;
		virtual void unbind() = 0;

	protected:

		// texture id
		unsigned int m_id;
		// texture size
		unsigned int m_width, m_height;
		// format of the texture object
		unsigned int m_format;
	};
}