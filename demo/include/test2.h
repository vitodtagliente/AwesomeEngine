#pragma once 

#include <awesome/awesome.h>
#include <cmath>
#include <glad/glad.h>

using namespace Awesome;
using namespace Awesome::Rendering;
using namespace Awesome::Scenegraph;

class Test2Application : public Application
{
public:
	Program program;
	Renderer* renderer{ nullptr };

	void init() override {
		auto vs = Shader::load("resources/shaders/test.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/test.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		renderer = Renderer::instance();

		test();
	}

	void test()
	{
		auto object = new Object("ciao");
	}
	
	void update(float deltaTime) override {

	}

	void render() override {
		/* use the program */
		program.use();


	}
};