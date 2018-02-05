#version 330 core

out vec4 fragColor;

in vec3 textColor;
in vec2 textCoords;

uniform sampler2D image;

void main(){
	fragColor = texture(image, textCoords) * vec4(textColor, 1.0);;
}