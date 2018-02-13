#version 330 core

in vec3 in_position;
in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(in_position, 1.0);
	TexCoord = aTexCoord;
}