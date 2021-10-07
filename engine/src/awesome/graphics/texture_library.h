/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>
#include <vector>

#include "texture.h"

class TextureLibrary
{
public:

	TextureLibrary();
	~TextureLibrary();

	void clear();

	// load textures form path
	unsigned int load(const std::string& path);
	// load texture given filenames
	unsigned int load(const std::vector<std::string>& files);

	// add a texture
	Texture* const add(const std::string& name, const std::string& filename);
	bool add(const std::string& name, Texture* const texture);
	// remove a texture
	bool remove(const std::string& name, bool free = false);

	// retrieve a texture
	Texture* const get(const std::string& name) const;

	// retrieve all textures
	const std::map<std::string, Texture*>& getTextures() const { return m_textures; }

private:

	// cached textures
	std::map<std::string, Texture*> m_textures;

};