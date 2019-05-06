#pragma once

#include "../texture.h"

namespace awesome
{
	class TextureGL final : public Texture
	{
	public:

		TextureGL(const unsigned char* const t_data, const uint t_width, const uint t_height,
			const uint t_components, const Options& t_options = Options{});
		~TextureGL();

		virtual void bind() override;
		void bind(const uint t_slot);
		virtual void unbind() override;
	};
}