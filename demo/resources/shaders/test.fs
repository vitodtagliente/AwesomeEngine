#version 330 core

out vec4 fragColor;
uniform vec4 inColor;

void main(){
	fragColor = inColor;
}