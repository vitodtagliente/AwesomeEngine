#pragma once

#include <awesome/graphics/texture.h>

namespace awesome
{
	class TextureGL final : public Texture
	{
	public:

		TextureGL(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height,
			const unsigned int t_components, const Options& t_options = Options{});
		~TextureGL();

		virtual void bind() override;
		void bind(const unsigned int t_slot);
		virtual void unbind() override;
	};
}