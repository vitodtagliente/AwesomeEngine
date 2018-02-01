#pragma once 

#include <awesome/awesome.h>
#include <cmath>
#include <glad/glad.h>

using namespace Awesome;
using namespace Awesome::Rendering;

class TestApplication : public Application
{
public:
	float color[4]{ 1.0f, 0.0f,0.0f,1.0f };
	Triangle triangle;
	Program program;

	void init() override {
		auto vs = Shader::load("resources/shaders/test.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/test.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		triangle.init();
	}
	
	void update(float deltaTime) override {
		color[0] = sin(deltaTime) * 0.5f + 0.5f;
		color[1] = cos(deltaTime) * 0.5f + 0.5f;
	}

	void render() override {
		/* use the program */
		program.use();
		/* clear the screen background */
		//glClearBufferfv(GL_COLOR, 0, color);
		/* draw the triangle */
		triangle.draw();
	}
};