#pragma once

#include <initializer_list>
#include <map>
#include <string>
#include <vector>

namespace awesome
{
	class GraphicsModule;
	class Texture;

	class TextureLibrary
	{
	public:

		TextureLibrary(GraphicsModule* t_graphicsModules);
		~TextureLibrary();

		void clear();

		// load textures form path
		unsigned int load(const std::string& t_path);
		// load texture given filenames
		unsigned int load(const std::vector<std::string>& t_files);
		unsigned int load(const std::initializer_list<std::string>& t_files);

		// add a texture
		Texture* const add(const std::string& t_name, const std::string& t_filename);
		bool add(const std::string& t_name, Texture* const t_texture);
		// remove a texture
		bool remove(const std::string& t_name, const bool t_delete = true);

		// retrieve a texture
		Texture* const get(const std::string& t_name) const;

	private:

		// graphics api
		GraphicsModule* m_graphics;
		// cached textures
		std::map<std::string, Texture*> m_textures;

	};
}