#pragma once 

#include <awesome/awesome.h>
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	Object* sprite_object;
	Camera camera;

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
		sprite_component->material = new Material();
		sprite_component->material->program = &program;

		sprite_object->transform.position.x = 0.0f;
		sprite_object->transform.rotation.z = 20.0f;
		
		/* init camera */
		camera.transform.position.z = -.2f;

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
		program.setMat4("projection", camera.getProjection());
		program.setMat4("view", camera.getView());
		program.setMat4("model", sprite_object->transform.get());
		/* draw objects */
		renderer->render();
	}
};