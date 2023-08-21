#include "texture_library.h"

#include <SDL3/SDL_image.h>

extern SDL_Renderer* sdl_renderer;

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
			std::unique_ptr<Texture> texture = std::make_unique<Texture>(path);
			if (*texture)
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