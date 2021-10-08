#include "shader_library.h"

ShaderLibrary::ShaderLibrary()
	: m_shaders()
{
	m_shaders.insert(std::make_pair(names::ColorShader, R"(
			#shader vertex

			#version 330 core
 
			// an attribute is an input (in) to a vertex shader.
			// It will receive data from a buffer
			in vec4 a_position;
			in vec4 a_color;

			out vec4 v_color;
 
			// all shaders have a main function
			void main() {
 
				// gl_Position is a special variable a vertex shader
				// is responsible for setting
				gl_Position = a_position;
				v_color = a_color;
			}

			#shader fragment

			#version 330 core

			// fragment shaders don't have a default precision so we need
			// to pick one. highp is a good default. It means "high precision"
			precision highp float;
 
			in vec4 v_color;
			out vec4 outColor;
 
			void main() {
				// Just set the output to a constant reddish-purple
				outColor = v_color;
			}		
		)"
	));
	m_shaders.insert(std::make_pair(names::GizmosShader, R"(
			#shader vertex

			#version 330 core
 
			// an attribute is an input (in) to a vertex shader.
			// It will receive data from a buffer
			in vec4 a_position;
			in vec4 a_color;

			out vec4 v_color;

			uniform mat4 u_matrix;
 
			// all shaders have a main function
			void main() {
 
				// gl_Position is a special variable a vertex shader
				// is responsible for setting
				gl_Position = u_matrix * a_position;
				v_color = a_color;
			}

			#shader fragment

			#version 330 core

			// fragment shaders don't have a default precision so we need
			// to pick one. highp is a good default. It means "high precision"
			precision highp float;
 
			in vec4 v_color;
			out vec4 outColor;
 
			void main() {
				// Just set the output to a constant reddish-purple
				outColor = v_color;
			}		
		)"
	));
	m_shaders.insert(std::make_pair(names::SpriteBatchShader, R"(
			#shader vertex

			#version 330 core
 
			// an attribute is an input (in) to a vertex shader.
			// It will receive data from a buffer
			in vec4 a_position;
			in vec2 a_texcoord;
			in vec4 a_crop;
			in mat4 a_transform;

			uniform mat4 u_matrix;
 
			// a varying to pass the texture coordinates to the fragment shader
			out vec2 v_texcoord;
			out vec4 v_crop;
 
			void main() {
				// Multiply the position by the matrix.
				// gl_Position = u_matrix * a_transform * a_position;
				gl_Position = u_matrix * a_transform * a_position;
 
				// Pass the texcoord to the fragment shader.
				v_texcoord = a_texcoord;
				v_crop = a_crop;
			}

			#shader fragment

			#version 330 core
			precision highp float;
 
			// Passed in from the vertex shader.
			in vec2 v_texcoord;
			in vec4 v_crop;
 
			// The texture.
			uniform sampler2D u_texture;
 
			out vec4 outColor;
 
			void main() {
				outColor = texture(u_texture, clamp(v_texcoord * v_crop.zw + v_crop.xy, vec2(0, 0), vec2(1, 1)));
				// outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			}
		)"
	));
	m_shaders.insert(std::make_pair(names::TextureShader, R"(
			#shader vertex

			#version 330 core
 
			// an attribute is an input (in) to a vertex shader.
			// It will receive data from a buffer
			in vec4 a_position;
			in vec2 a_texcoord;

			uniform mat4 u_matrix;
 
			// a varying to pass the texture coordinates to the fragment shader
			out vec2 v_texcoord;
			out vec4 v_crop;
 
			void main() {
				// Multiply the position by the matrix.
				gl_Position = a_position;
 
				// Pass the texcoord to the fragment shader.
				v_texcoord = a_texcoord;
			}

			#shader fragment

			#version 330 core
			precision highp float;
 
			// Passed in from the vertex shader.
			in vec2 v_texcoord;
 
			// The texture.
			uniform sampler2D u_texture;
 
			out vec4 outColor;
 
			void main() {
				outColor = texture(u_texture, v_texcoord);
			}
		)"
	));
}

const std::string ShaderLibrary::names::ColorShader = "Color";
const std::string ShaderLibrary::names::GizmosShader = "Gizmos";
const std::string ShaderLibrary::names::SpriteBatchShader = "SpriteBatch";
const std::string ShaderLibrary::names::TextureShader = "Texture";