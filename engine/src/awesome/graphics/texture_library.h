/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <vector>

#include <awesome/asset/image_asset.h>
#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>

#include "texture.h"

namespace graphics
{
	class TextureLibrary : public Singleton<TextureLibrary>
	{
	public:
		friend class GraphicsModule;

		TexturePtr find(const ImageAsset& image);

	private:
		void flush();

		std::vector<ImageAsset> m_loadQueue;
		std::map<uuid, TexturePtr> m_textures;
	};
}