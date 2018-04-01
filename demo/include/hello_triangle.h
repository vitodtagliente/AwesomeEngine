#pragma once 

#include <awesome/awesome.h>

using namespace Awesome;

class HelloTriangleApplication : public Application
{
public:
	Program program;
	glm::vec4 color{ 1.0f, 0.0f, 0.0f, 1.0f };

	HelloTriangleApplication()
	{
		getWindow()->setTitle("AwesomeEngine::HelloTriangle");
	}

	void configure() override
	{
		auto vs = Shader::load("resources/shaders/hello_triangle.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/hello_triangle.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		// fill scene objects
		auto triangle_object = getScene()->spawn<Object>("triangle");
		auto triangle_component = triangle_object->addComponent<MeshRenderingComponent>();
		triangle_component->mesh = Primitive::generate<Triangle>();

		// init camera 
		auto camera = getScene()->spawn<Camera>("camera");
		
		// use program
		program.use();
		// set the fragment color
		int location = program.getUniformLocation("inColor");
		program.setVec4(location, color);
	}
};