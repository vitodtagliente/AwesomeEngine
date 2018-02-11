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
	Scene* scene{ nullptr };

	void init() override 
	{
		auto vs = Shader::load("resources/shaders/test.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/test.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		renderer = Renderer::instance();
		renderer->scene = new Scene();
		scene = renderer->scene;

		/* fill scene objects */
		auto triangle_object = scene->spawn<Object>("triangle");
		auto triangle_component = triangle_object->addComponent<MeshRenderingComponent>(new MeshRenderingComponent());
		triangle_component->mesh = new Triangle();

		/* init renderer */
		renderer->init();
	}
	
	void update(float delta_time) override 
	{
		renderer->update(delta_time);
	}

	void render() override 
	{
		/* use the program */
		program.use();

		renderer->render();
	}
};