#pragma once

#include <map>
#include <string>

namespace awesome
{
	namespace assets
	{
		std::map<std::string, std::string> shaders = {

			{ "solid", R"(
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

			{ "sprite", R"(
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

			{ "sprite_atlas", R"(
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
				uniform vec4 u_Crop;

				in vec2 v_TexCoord;

				void main()
				{
					vec2 cropCoords;
					cropCoords.x = (v_TexCoord.x * u_Crop.z + u_Crop.x);
					cropCoords.y = (v_TexCoord.y * u_Crop.w + u_Crop.y);
					vec4 texColor = texture(u_Texture, cropCoords);
					fragColor = texColor;
				}
			)" }

		};
	}
}