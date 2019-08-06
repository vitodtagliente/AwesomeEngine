#pragma once

#include <initializer_list>
#include <map>
#include <string>
#include <vector>

namespace awesome
{
	class GraphicsAPI;
	class Texture;

	class TextureLibrary
	{
	public:

		TextureLibrary(GraphicsAPI* t_api);
		~TextureLibrary();

		void clear();

		// load textures form path
		unsigned int load(const std::string& t_path);
		// load texture given filenames
		unsigned int load(const std::vector<std::string>& t_files);

		// add a texture
		Texture* const add(const std::string& t_name, const std::string& t_filename);
		bool add(const std::string& t_name, Texture* const t_texture);
		// remove a texture
		bool remove(const std::string& t_name, const bool t_delete = true);

		// retrieve a texture
		Texture* const get(const std::string& t_name) const;

		// retrieve all textures
		const std::map<std::string, Texture*>& getTextures() const { return m_textures; }

	private:

		// graphics api
		GraphicsAPI* m_api;
		// cached textures
		std::map<std::string, Texture*> m_textures;

	};
}