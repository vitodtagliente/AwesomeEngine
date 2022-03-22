#include "texture_library.h"

#include <awesome/data/asset_library.h>

namespace graphics
{
	TextureLibrary::TextureLibrary()
		: m_textures()
	{
	}

	std::shared_ptr<Texture> TextureLibrary::find(const uuid& id)
	{
		const auto& it = m_textures.find(id);
		if (it != m_textures.end())
		{
			return it->second;
		}
		else
		{
			std::shared_ptr<Texture> texture = create(id);
			if (texture)
			{
				m_textures.insert(std::make_pair(id, texture));
			}
			return texture;
		}
	}

	std::shared_ptr<Texture> TextureLibrary::create(const uuid& id)
	{
		std::shared_ptr<ImageAsset> asset = std::static_pointer_cast<ImageAsset>(AssetLibrary::instance()->find(id));
		if (asset)
		{
			const Image& image = asset->data;
			return std::make_shared<Texture>(image.data.get(), image.width, image.height, image.channels);
		}
		return nullptr;
	}
}