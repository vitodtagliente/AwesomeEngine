#pragma once

#include <map>
#include <string>

namespace awesome
{
	class Texture;

	class TextureLibrary
	{
	public:

		TextureLibrary();
		~TextureLibrary();

		void clear();

		// load textures form path
		unsigned int loadTextures(const std::string& t_path);

		Texture* const getTexture(const std::string& t_name) const;

	private:

		// cached textures
		std::map<std::string, Texture*> m_textures;

	};
}