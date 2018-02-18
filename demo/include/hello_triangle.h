#pragma once 

#include <awesome/awesome.h>
#include <cmath>
#include <glad/glad.h>

using namespace Awesome;
using namespace Awesome::Rendering;
using namespace Awesome::Scenegraph;

class HelloTriangleApplication : public Application
{
public:
	Program program;
	Renderer* renderer{ nullptr };
	Scene* scene{ nullptr };

	HelloTriangleApplication()
	{
		getWindow()->setTitle("AwesomeEngine::HelloTriangle");
	}

	void init() override 
	{
		auto vs = Shader::load("resources/shaders/hello_triangle.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/hello_triangle.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		renderer = Renderer::instance();
		renderer->scene = new Scene("triangle_scene");
		scene = renderer->scene;

		/* fill scene objects */
		auto triangle_object = scene->spawn<Object>("triangle");
		auto triangle_component = triangle_object->addComponent<MeshRenderingComponent>();
		triangle_component->mesh = Primitive::generate<Triangle>();
		
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
		/* set the color */
		glUniform4f(program.getUniformLocation("inColor"), 1.0f, 0.0f, 0.0f, 1.0f);
		/* draw objects */
		renderer->render();
	}
};