#pragma once 

#include <awesome/awesome.h>
#include <cmath>
#include <glad/glad.h>

using namespace Awesome;
using namespace Awesome::Rendering;

class TextureDemoApplication : public Application
{
public:
	Triangle triangle;
	Square square;
	Program program;
	Texture texture;
	int colorAttributeLocation{ 0 };

	void init() override {
		auto vs = Shader::load("resources/shaders/texture.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/texture.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		triangle.init();
		square.init();

		texture.load("resources/textures/wall.jpg");

		colorAttributeLocation = program.getUniformLocation("inColor");
	}

	void update(float deltaTime) override {

	}

	void render() override {
		/* use the program */
		program.use();
		/* draw the triangle */
	}
};