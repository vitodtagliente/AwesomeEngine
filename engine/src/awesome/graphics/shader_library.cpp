#include "shader_library.h"

ShaderLibrary::ShaderLibrary()
	: m_shaders()
{
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
}

const std::string ShaderLibrary::names::GizmosShader = "Gizmos";