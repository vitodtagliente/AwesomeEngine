#pragma once 

#include <dreamkeeper/dreamkeeper.h>
#include <iostream>

using namespace Dreamkeeper;
using namespace Core;
using namespace Shading;

class LoadingShadersApplication : public Application
{
private:
	VertexShader vs{ "vertex-shader" };
	FragmentShader fs{ "fragment-shader" };
	Program program;
	VAO vao;

public:
	~LoadingShadersApplication() {
		program.free(true);
		vao.free();
	}

	void init() override {	
		Utility::Log::instance()->std_output = true;
		vao.bind();
		glPointSize(10.f);

		vs.compile("resources/shaders/loading_shaders.vs");
		fs.compile("resources/shaders/loading_shaders.fs");

		program.linkShaders({ &vs, &fs });
		if (program.compile() == false)
			close();
	}

	void update(float deltaTime) override {
		
	}

	void render() override {
		program.use();

		// draw a point
		glDrawArrays(GL_POINTS, 0, 1);
	}
};