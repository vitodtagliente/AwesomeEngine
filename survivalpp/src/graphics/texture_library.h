/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <vector>

#include "core/singleton.h"

#include "texture.h"

namespace graphics
{
	class TextureLibrary : public Singleton<TextureLibrary>
	{
	public:
		friend class GraphicsModule;

		Texture* const find(const std::filesystem::path& path);

		void clear();

	private:
		std::map<std::filesystem::path, std::unique_ptr<Texture>> m_textures;
	};
}