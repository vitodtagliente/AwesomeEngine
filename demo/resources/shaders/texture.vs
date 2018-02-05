#version 330 core

in vec3 in_position;
in vec3 in_color;
in vec2 in_uv;

out vec3 textColor;
out vec2 textCoords;

void main()
{
	gl_Position = vec4(in_position, 1.0);
	textColor = in_color;
	textCoords = in_uv;
}