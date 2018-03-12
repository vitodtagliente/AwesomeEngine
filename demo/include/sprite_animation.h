#pragma once 

#include <awesome/awesome.h>
#include <random>

using namespace Awesome;
using namespace Awesome::Rendering;
using namespace Awesome::Scenegraph;
using namespace Awesome::Gameplay;

class SpriteAnimationApplication : public Application
{
public:
	Program program;
	Texture texture;
	Object* sprite_object;
	Camera* camera;

	SpriteAnimationApplication()
	{
		getWindow()->setTitle("AwesomeEngine::SpriteAnimation");
	}
	
	void init() override
	{
		auto vs = Shader::load("resources/shaders/texture.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/texture.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();

		if (!texture.load("resources/textures/bear.png"))
			exit(-1);

		sprite_object = getScene()->spawn<Object>("sprite");
		auto sprite_component = sprite_object->addComponent<SpriteRenderingComponent>();
		sprite_component->texture = &texture;
		sprite_component->material = new Material();
		sprite_component->material->program = &program;
		auto sprite_animation_component = sprite_object->addComponent<SpriteAnimationComponent>();

		SpriteAnimation walk_right;
		walk_right.frames.push_back(SpriteAnimationData{ &texture, Math::Rect{ 0.4f, 0.375f, 0.2f, 0.125f }, 400.0f });
		walk_right.frames.push_back(SpriteAnimationData{ &texture, Math::Rect{ 0.6f, 0.375f, 0.2f, 0.125f }, 400.0f });

		sprite_animation_component->animations["walk_right"] = walk_right;

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