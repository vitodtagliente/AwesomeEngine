/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>

#include <awesome/asset/image_asset.h>
#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>

#include "texture.h"

namespace graphics
{
	class TextureLibrary : public Singleton<TextureLibrary>
	{
	public:
		TexturePtr find(ImageAsset& image);

	private:
		std::map<uuid, TexturePtr> m_textures;
	};
}