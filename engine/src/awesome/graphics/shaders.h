#pragma once

#include <map>
#include <string>

// collection of default engine shaders
// The engine should provide some basic shaders by itself

namespace awesome
{
	struct Shaders
	{
		Shaders() = delete;

		struct params
		{
			params() = delete;

			static const std::string ModelViewProjectionMatrix;
			static const std::string ViewProjectionMatrix;
			static const std::string ModelTransformMatrix;
			static const std::string Texture;
			static const std::string Color;
			static const std::string TextureCropping;
		};

		struct names
		{
			names() = delete;

			static const std::string ColorShader;
			static const std::string TextureShader;
			static const std::string CroppedTextureShader;
		};
	};
}