#pragma once 

#include <awesome/awesome.h>
#include <random>

using namespace Awesome;

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

	float range(float min, float max) const {
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_real_distribution<> distr(min, max); // define the range
		return distr(eng);
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
			
			sprite_component->crop(Rect{
				range(0.0f, 0.5f), range(0.0f, 0.5f),
				range(0.75f, 1.0f), range(0.75f, 1.0f)
			});

			sprite_object->transform.position.x = range(-1.0f, 1.0f);
			sprite_object->transform.position.y = range(-1.0f, 1.0f);
			sprite_object->transform.scale.x = range(0.3f, 0.5f);
			sprite_object->transform.scale.y = range(0.3f, 0.5f);
			sprite_object->transform.rotation.z = range(0.0f, 360.0f);
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