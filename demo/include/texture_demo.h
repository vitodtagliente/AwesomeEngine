#pragma once 

#include <awesome/awesome.h>

using namespace Awesome;

class TextureDemoApplication : public Application
{
public:
	Program program;
	Texture texture;
	Object* sprite_object;
	Camera* camera;

	TextureDemoApplication()
	{
		getWindow()->setTitle("AwesomeEngine::TextureDemo");
	}

	void configure() override
	{
		auto vs = Shader::load("resources/shaders/texture.vs", ShaderType::VertexShader);
		auto fs = Shader::load("resources/shaders/texture.fs", ShaderType::FragmentShader);

		program.linkShaders({ vs, fs });
		program.compile();
		
		if (!texture.load("resources/textures/wall.jpg"))
			exit(-1);

		/* fill scene objects */
		sprite_object = getScene()->spawn<Object>("sprite");
		auto sprite_component = sprite_object->addComponent<SpriteRenderingComponent>();
		sprite_component->texture = &texture;
		sprite_component->material = new Material();
		sprite_component->material->program = &program;
		
		/* init camera */
		camera = getScene()->spawn<Camera>("camera");
		camera->transform.position.z = -0.2f;
	}
};