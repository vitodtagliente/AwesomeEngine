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
	glm::vec4 color{ 1.0f, 0.0f, 0.0f, 1.0f };

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

		/* fill scene objects */
		auto triangle_object = getScene()->spawn<Object>("triangle");
		auto triangle_component = triangle_object->addComponent<MeshRenderingComponent>();
		triangle_component->mesh = Primitive::generate<Triangle>();
	}
	
	void update(float delta_time) override 
	{

	}

	void render() override 
	{
		program.setVec4("inColor", color);
	}
};