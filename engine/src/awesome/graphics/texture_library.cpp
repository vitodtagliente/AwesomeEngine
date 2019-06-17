#include "texture_library.h"

namespace awesome
{

	TextureLibrary::TextureLibrary()
		: m_textures()
	{

	}

	TextureLibrary::~TextureLibrary()
	{

	}

	void TextureLibrary::clear()
	{

	}

	unsigned int TextureLibrary::loadTextures(const std::string& t_path)
	{
		return 0;
	}

	Texture* const TextureLibrary::getTexture(const std::string& t_name) const
	{
		const auto it = m_textures.find(t_name);
		if (it != m_textures.end())
		{
			return it->second;
		}
		return nullptr;
	}

}