#pragma once 

#include <awesome/awesome.h>
#include <cmath>
#include <glad/glad.h>

using namespace Awesome;
using namespace Awesome::Rendering;

class Test2Application : public Application
{
public:
	Program program;

	void init() override {
		auto vs = Shader::load("resources/shaders/test.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/test.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

	}
	
	void update(float deltaTime) override {

	}

	void render() override {
		/* use the program */
		program.use();


	}
};