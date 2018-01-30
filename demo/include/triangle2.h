#pragma once 

#include <dreamkeeper/dreamkeeper.h>
#include <iostream>

using namespace Dreamkeeper;
using namespace Dreamkeeper::Core;
using namespace Dreamkeeper::Shading;
using namespace Dreamkeeper::Primitives;

class Triangle2Application : public Application
{
private:
	VertexShader vs{ "vertex-shader" };
	FragmentShader fs{ "fragment-shader" };
	Program program;
	VAO vao;
	VBO vbo;
	Triangle triangle;

public:
	~Triangle2Application() {
		program.free(true);
		vbo.free();
		vao.free();
	}

	void init() override {
		Utility::Log::instance()->std_output = true;

		std::cout << GLVersion.major << " " << GLVersion.minor << std::endl;

		vs.compile("resources/shaders/triangle2.vs");
		fs.compile("resources/shaders/triangle2.fs");
		
		program.linkShaders({ &vs, &fs });
		if (program.compile() == false)
			close();

		triangle.finalize();
	}
	
	void update(float deltaTime) override {
		
	}

	void render() override {
		program.use();

		glClearColor(0.0, 0.0, 0.05, 1.0);
		triangle.bind();
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};