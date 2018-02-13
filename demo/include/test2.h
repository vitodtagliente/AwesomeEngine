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
	Texture texture;

	void init() override 
	{
		auto vs = Shader::load("resources/shaders/texture.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/texture.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		renderer = Renderer::instance();
		renderer->scene = new Scene("sprite_scene");
		scene = renderer->scene;

		if (!texture.load("resources/textures/wall.jpg"))
			exit(-1);

		/* fill scene objects */
		auto sprite = scene->spawn<Object>("sprite");
		auto sprite_component = sprite->addComponent<SpriteRenderingComponent>();
		sprite_component->texture = &texture;

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
		/* draw objects */
		renderer->render();
	}
};