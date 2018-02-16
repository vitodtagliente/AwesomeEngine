#version 330 core

in vec3 in_position;
in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(in_position, 1.0);
	TexCoord = aTexCoord;
}