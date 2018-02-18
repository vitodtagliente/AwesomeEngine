#pragma once 

#include <awesome/awesome.h>
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Awesome;
using namespace Awesome::Rendering;
using namespace Awesome::Scenegraph;

class TextureDemoApplication : public Application
{
public:
	Program program;
	Renderer* renderer{ nullptr };
	Scene* scene{ nullptr };
	Texture texture;
	glm::mat4 projection, view;
	Object* sprite_object;

	TextureDemoApplication()
	{
		getWindow()->setTitle("AwesomeEngine::TextureDemo");
	}

	void init() override
	{
		auto vs = Shader::load("resources/shaders/texture.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/texture.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		renderer = Renderer::instance();
		renderer->scene->name = "texture_scene";
		scene = renderer->scene;

		if (!texture.load("resources/textures/wall.jpg"))
			exit(-1);

		/* fill scene objects */
		sprite_object = scene->spawn<Object>("sprite");
		auto sprite_component = sprite_object->addComponent<SpriteRenderingComponent>();
		sprite_component->texture = &texture;
		sprite_object->transform.position.x = 0.0f;
		sprite_object->transform.rotation.z = 20.0f;
						
		/* init renderer */
		renderer->init();

		/* setup projection */
		projection = glm::ortho(-4.0f / 3.0f, 4.0f / 3.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		view = glm::mat4(1.0f);
	}

	void update(float delta_time) override
	{
		renderer->update(delta_time);
	}

	void render() override
	{
		/* use the program */
		program.use(); 
		glUniformMatrix4fv(program.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(program.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(program.getUniformLocation("model"), 1, GL_FALSE, 
			glm::value_ptr(sprite_object->transform.get())
		);
		/* draw objects */
		renderer->render();
	}
};