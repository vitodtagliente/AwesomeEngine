#include "texture_library.h"

namespace graphics
{
	TexturePtr TextureLibrary::find(ImageAsset& image)
	{
		const auto& it = m_textures.find(image.id);
		if (it != m_textures.end())
		{
			return it->second;
		}
		else
		{
			if (!image || image.state == Asset::State::Error) return nullptr;

			TexturePtr texture = nullptr;
			if (image.state == Asset::State::Ready)
			{
				const Image& image_data = *image.resource;
				texture = std::make_shared<Texture>(image_data.data.get(), image_data.width, image_data.height, image_data.channels);
			}
			else
			{
				image.load([&image, &texture]() -> void
					{
						const Image& image_data = *image.resource;
						texture = std::make_shared<Texture>(image_data.data.get(), image_data.width, image_data.height, image_data.channels);
					}
				);
			}
			m_textures.insert(std::make_pair(image.id, texture));
			return texture;
		}
	}
}