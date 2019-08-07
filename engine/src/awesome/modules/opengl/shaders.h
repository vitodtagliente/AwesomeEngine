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

				out vec4 out_fragColor;

				uniform vec4 u_color;

				void main()
				{
					out_fragColor = u_color;
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
			)" }

		};
	}
}