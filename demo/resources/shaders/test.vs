#version 330 core

in vec3 in_position;

void main()
{
	gl_Position.xyz = in_position;
	gl_Position.w = 1.0;
}