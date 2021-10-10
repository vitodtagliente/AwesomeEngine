/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

namespace graphics
{
	class ShaderLibrary
	{
	public:
		ShaderLibrary();

		const std::map<std::string, std::string>& getShaders() const { return m_shaders; }

		struct names
		{
			names() = delete;

			static const std::string ColorShader;
			static const std::string GizmosShader;
			static const std::string SpriteBatchShader;
			static const std::string TextureShader;
		};

	private:
		std::map<std::string, std::string> m_shaders;
	};
}