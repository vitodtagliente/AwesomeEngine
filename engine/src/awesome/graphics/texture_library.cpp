#include "texture_library.h"

#include <fstream>
#include <awesome/data/image.h>
#include "texture.h"
#include "graphics_api.h"

namespace awesome
{

	TextureLibrary::TextureLibrary(GraphicsAPI* const t_api)
		: m_api(t_api)
		, m_textures()
	{

	}

	TextureLibrary::~TextureLibrary()
	{

	}

	void TextureLibrary::clear()
	{

	}

	unsigned int TextureLibrary::load(const std::string& t_path)
	{
		// #todo retrieve all file in a folder
		return 0;
	}

	unsigned int TextureLibrary::load(const std::vector<std::string>& t_files)
	{
		unsigned int count = 0;
		for (const std::string& filename : t_files)
		{
			// #todo: extract the filename
			if (add(filename, filename))
				++count;
		}
		return count;
	}

	Texture* const TextureLibrary::add(const std::string& t_name, const std::string& t_filename)
	{
		const auto it = m_textures.find(t_name);
		if (it == m_textures.end())
		{
			Image img(t_filename);
			Texture* texture = m_api->createTexture(
				img.data(), img.getWidth(), img.getHeight(), img.getComponents()
			);
			m_textures.insert({ t_name, texture });
			return texture;
		}
		return nullptr;
	}

	bool TextureLibrary::add(const std::string& t_name, Texture* const t_texture)
	{
		const auto it = m_textures.find(t_name);
		if (it == m_textures.end())
		{
			m_textures.insert({ t_name, t_texture });
			return true;
		}
		return false;
	}

	bool TextureLibrary::remove(const std::string& t_name, const bool t_delete /*= true*/)
	{
		const auto it = m_textures.find(t_name);
		if (it != m_textures.end())
		{
			if (t_delete)
			{
				delete it->second;
			}
			m_textures.erase(it);
			return true;
		}
		return false;
	}

	Texture* const TextureLibrary::get(const std::string& t_name) const
	{
		const auto it = m_textures.find(t_name);
		if (it != m_textures.end())
		{
			return it->second;
		}
		return nullptr;
	}

}