/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>

#include "texture.h"

namespace graphics
{
	class TextureLibrary : public Singleton<TextureLibrary>
	{
	public:
		TextureLibrary();
		~TextureLibrary() = default;

		std::shared_ptr<Texture> find(const uuid& id);

	private:
		std::shared_ptr<Texture> create(const uuid& id);

		std::map<uuid, std::shared_ptr<Texture>> m_textures;
	};
}