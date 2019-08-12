#include "shaders.h"

namespace awesome
{
	// shader names

	const std::string Shaders::names::ColorShader = "color";
	const std::string Shaders::names::TextureShader = "texture";
	const std::string Shaders::names::CroppedTextureShader = "cropped_texture";

	// shader param names

	const std::string Shaders::params::ModelViewProjectionMatrix = "u_ModelViewProjectionMatrix";
	const std::string Shaders::params::ViewProjectionMatrix = "u_ViewProjectionMatrix";
	const std::string Shaders::params::ModelTransformMatrix = "u_Transform";
	const std::string Shaders::params::Color = "u_Color";
	const std::string Shaders::params::Texture = "u_Texture";
	const std::string Shaders::params::TextureCropping = "u_TextureCropping";

	// sources

	// const std::map<std::string, std::string> Shaders::sources = {};
	const std::map<std::string, std::string> Shaders::sources = {

		{ Shaders::names::ColorShader, R"(
			#shader vertex

			#version 330 core

			layout(location = 0) in vec4 in_vertex;

			uniform mat4 u_ModelViewProjectionMatrix;

			void main()
			{
				gl_Position = u_ModelViewProjectionMatrix * in_vertex;
			}

			#shader fragment

			#version 330 core

			out vec4 fragColor;

			uniform vec4 u_Color;

			void main()
			{
				fragColor = u_Color;
			}			
		)" },

		{ Shaders::names::TextureShader, R"(
			#shader vertex

			#version 330 core

			layout(location = 0) in vec4 position;
			layout(location = 1) in vec2 texCoord;

			out vec2 v_TexCoord;

			uniform mat4 u_ModelViewProjectionMatrix;

			void main()
			{
				gl_Position = u_ModelViewProjectionMatrix * position;
				v_TexCoord = texCoord;
			}

			#shader fragment

			#version 330 core

			out vec4 fragColor;

			uniform vec4 u_Color;
			uniform sampler2D u_Texture;

			in vec2 v_TexCoord;

			void main()
			{
				vec4 texColor = texture(u_Texture, v_TexCoord);
				fragColor = texColor;
			}
		)" },

		{ Shaders::names::CroppedTextureShader, R"(
			#shader vertex

			#version 330 core

			layout(location = 0) in vec4 position;
			layout(location = 1) in vec2 texCoord;

			out vec2 v_TexCoord;

			uniform mat4 u_ModelViewProjectionMatrix;

			void main()
			{
				gl_Position = u_ModelViewProjectionMatrix * position;
				v_TexCoord = texCoord;
			}

			#shader fragment

			#version 330 core

			out vec4 fragColor;

			uniform vec4 u_Color;
			uniform sampler2D u_Texture;
			uniform vec4 u_TextureCropping;

			in vec2 v_TexCoord;

			void main()
			{
				vec2 croppingCoords;
				croppingCoords.x = (v_TexCoord.x * u_TextureCropping.z + u_TextureCropping.x);
				croppingCoords.y = (v_TexCoord.y * u_TextureCropping.w + u_TextureCropping.y);
				vec4 texColor = texture(u_Texture, croppingCoords);
				fragColor = texColor;
			}
		)" }

	};
}