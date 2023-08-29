#include "texture_library.h"

#include <vdtgraphics/image.h>

namespace graphics
{
	Texture* const TextureLibrary::find(const std::filesystem::path& path)
	{
		const auto& it = m_textures.find(path);
		if (it != m_textures.end())
		{
			return it->second.get();
		}
		else
		{
			Image img = Image::load(path);
			std::unique_ptr<Texture> texture = std::make_unique<Texture>(img.data.get(), img.width, img.height, img.channels);
			if (texture != nullptr)
			{
				const auto& pair = m_textures.insert(std::make_pair(path, std::move(texture))).first;
				return pair->second.get();
			}
			return nullptr;
		}
	}
	
	void TextureLibrary::clear()
	{
		m_textures.clear();
	}
}