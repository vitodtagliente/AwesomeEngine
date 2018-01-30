#pragma once 

#include <awesome/awesome.h>
#include <iostream>

#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

using namespace Awesome;
using namespace Awesome::Core;
using namespace Awesome::Shading;

class TextureApplication : public Application
{
private:
	VertexShader vs{ "vertex-shader" };
	FragmentShader fs{ "fragment-shader" };
	Program program;
	VAO vao;
	VBO vbo;
	glm::mat4 cube_transform;
	glm::mat4 projection;

public:
	~TextureApplication() {
		program.free(true);
		vbo.free();
		vao.free();
	}

	void init() override {
		Utility::Log::instance()->std_output = true;

		std::cout << GLVersion.major << " " << GLVersion.minor << std::endl;

		vs.compile("resources/shaders/texture.vs");
		fs.compile("resources/shaders/texture.fs");
		
		program.linkShaders({ &vs, &fs });
		if (program.compile() == false)
			close();

		/* cube vertices */
		const float vertices[] = {
			-0.25f, 0.25f, -0.25f,
			-0.25f, -0.25f, -0.25f,
			0.25f, -0.25f, -0.25f,

			0.25f, -0.25f, -0.25f,
			-0.25f, 0.25f, -0.25f,
			-0.25f, 0.25f, -0.25f,
		};
		vao.bind();
		vbo.bind();

		vbo.allocate(sizeof(vertices), vertices);
		VertexArrayAttribute position;
		position.count = 3;
		position.format(0, 0);
		position.enable();

		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		glUniformMatrix4fv(program.getUniformLocation("projection"), 1, GL_FALSE, &projection[0][0]);
	}

	void update(float deltaTime) override {
		
	}

	void render() override {
		program.use();

		glClearColor(0.0, 0.0, 0.05, 1.0);
		program.use();

		glUniformMatrix4fv(program.getUniformLocation("projection"), 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(program.getUniformLocation("model_view"), 1, GL_FALSE, &cube_transform[0][0]);

		// Draw the triangles
		glDrawArrays(GL_TRIANGLES, 0, 2);
	}
};