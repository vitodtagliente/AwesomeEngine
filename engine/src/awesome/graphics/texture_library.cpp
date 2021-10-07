#include "texture_library.h"

#include <awesome/data/image.h>

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

unsigned int TextureLibrary::load(const std::string& path)
{
	// #todo retrieve all file in a folder
	return 0;
}

unsigned int TextureLibrary::load(const std::vector<std::string>& files)
{
	unsigned int count = 0;
	for (const std::string& filename : files)
	{
		// #todo: extract the filename
		if (add(filename, filename))
			++count;
	}
	return count;
}

Texture* const TextureLibrary::add(const std::string& name, const std::string& filename)
{
	const auto it = m_textures.find(name);
	if (it == m_textures.end())
	{
		Image img(filename);
		Texture* texture = new Texture(
			img.data(), img.getWidth(), img.getHeight(), img.getChannels()
		);
		m_textures.insert({ name, texture });
		return texture;
	}
	return nullptr;
}

bool TextureLibrary::add(const std::string& name, Texture* const texture)
{
	const auto it = m_textures.find(name);
	if (it == m_textures.end())
	{
		m_textures.insert({ name, texture });
		return true;
	}
	return false;
}

bool TextureLibrary::remove(const std::string& name, const bool free /*= false*/)
{
	const auto it = m_textures.find(name);
	if (it != m_textures.end())
	{
		if (free)
		{
			delete it->second;
		}
		m_textures.erase(it);
		return true;
	}
	return false;
}

Texture* const TextureLibrary::get(const std::string& name) const
{
	const auto it = m_textures.find(name);
	if (it != m_textures.end())
	{
		return it->second;
	}
	return nullptr;
}