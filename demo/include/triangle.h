#pragma once 

#include <dreamkeeper/dreamkeeper.h>
#include <iostream>

using namespace Dreamkeeper;
using namespace Dreamkeeper::Core;
using namespace Dreamkeeper::Shading;

class TriangleApplication : public Application
{
private:
	VertexShader vs{ "vertex-shader" };
	FragmentShader fs{ "fragment-shader" };
	Program program;
	VAO vao;
	VBO vbo;

public:
	~TriangleApplication() {
		program.free(true);
		vbo.free();
		vao.free();
	}

	void init() override {
		Utility::Log::instance()->std_output = true;

		std::cout << GLVersion.major << " " << GLVersion.minor << std::endl;

		vs.compile("resources/shaders/triangle.vs");
		fs.compile("resources/shaders/triangle.fs");

		if (GL_VERSION_4_5)
			std::cout << "4.5" << std::endl;

		program.linkShaders({ &vs, &fs });
		if (program.compile() == false)
			close();

		const float vertices[] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.0f,  0.75f, 0.0f,
		};
		vao.bind();
		vbo.bind();
			
		vbo.allocate(sizeof(vertices), vertices);
		VertexArrayAttribute position;
		position.count = 3;
		position.format(0, 3 * sizeof(float));
		position.enable();
	}
	
	void update(float deltaTime) override {
		
	}

	void render() override {
		program.use();

		glClearColor(0.0, 0.0, 0.05, 1.0);
		// load configurations
		vao.bind();
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};