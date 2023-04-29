#include "texture_library.h"

namespace graphics
{
	TexturePtr TextureLibrary::find(const ImageAsset& image)
	{
		const auto& it = m_textures.find(image.id);
		if (it != m_textures.end())
		{
			return it->second;
		}
		else
		{
			if (!image.ready()) return nullptr;

			const Image& image_data = *image.resource;
			TexturePtr texture = std::make_shared<Texture>(image_data.data.get(), image_data.width, image_data.height, image_data.channels);
			m_textures.insert(std::make_pair(image.id, texture));
			return texture;
		}
	}
}