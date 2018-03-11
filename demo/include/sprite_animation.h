#pragma once 

#include <awesome/awesome.h>
#include <random>

using namespace Awesome;
using namespace Awesome::Rendering;
using namespace Awesome::Scenegraph;

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