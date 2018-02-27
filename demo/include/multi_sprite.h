#pragma once 

#include <awesome/awesome.h>

using namespace Awesome;
using namespace Awesome::Rendering;
using namespace Awesome::Scenegraph;

class MultiSpriteApplication : public Application
{
public:
	Program program;
	Texture texture;
	Object* sprite_object;
	Camera* camera;
	const int max_sprites = 10;

	MultiSpriteApplication()
	{
		getWindow()->setTitle("AwesomeEngine::MultiSprite");
	}

	void init() override
	{
		auto vs = Shader::load("resources/shaders/texture.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/texture.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();
		
		if (!texture.load("resources/textures/fruit.png"))
			exit(-1);

		/* fill scene objects */
		for (int i = 0; i < max_sprites; i++)
		{
			sprite_object = getScene()->spawn<Object>("sprite" + i);
			auto sprite_component = sprite_object->addComponent<SpriteRenderingComponent>();
			sprite_component->texture = &texture;
			sprite_component->material = new Material();
			sprite_component->material->program = &program;

			sprite_object->transform.position.x = rand() % 5 - 2;
			sprite_object->transform.position.y = rand() % 5 - 2;
			sprite_object->transform.scale.x = 0.3f;
			sprite_object->transform.scale.y = 0.3f;
		}
		
		/* init camera */
		camera = getScene()->spawn<Camera>("camera");
		camera->transform.position.z = -.2f;
	}

	void update(float delta_time) override
	{

	}

	void render() override
	{		

	}
};