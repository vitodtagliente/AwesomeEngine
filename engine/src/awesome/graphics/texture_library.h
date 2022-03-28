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

		TexturePtr find(const uuid& id);

	private:
		TexturePtr create(const uuid& id);

		std::map<uuid, TexturePtr> m_textures;
	};
}