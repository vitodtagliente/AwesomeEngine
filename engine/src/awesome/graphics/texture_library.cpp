#include "texture_library.h"

#include <awesome/asset/asset_library.h>
#include <awesome/asset/image_asset.h>

namespace graphics
{
	TexturePtr TextureLibrary::find(const uuid& id)
	{
		const auto& it = m_textures.find(id);
		if (it != m_textures.end())
		{
			return it->second;
		}
		else
		{
			TexturePtr texture = create(id);
			if (texture)
			{
				m_textures.insert(std::make_pair(id, texture));
			}
			return texture;
		}
	}

	TexturePtr TextureLibrary::create(const uuid& id)
	{
		std::shared_ptr<ImageAsset> asset = std::static_pointer_cast<ImageAsset>(AssetLibrary::instance().find(id));
		if (asset!= nullptr && asset->state == Asset::State::Ready)
		{
			const Image& image = asset->data;
			return std::make_shared<Texture>(image.data.get(), image.width, image.height, image.channels);
		}
		return nullptr;
	}
}