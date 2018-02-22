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
		
		if (!texture.load("resources/textures/wall.jpg"))
			exit(-1);

		/* fill scene objects */
		sprite_object = getScene()->spawn<Object>("sprite");
		auto sprite_component = sprite_object->addComponent<SpriteRenderingComponent>();
		sprite_component->texture = &texture;
		sprite_component->material = new Material();
		sprite_component->material->program = &program;

		sprite_object->transform.position.x = 0.0f;
		sprite_object->transform.rotation.z = 20.0f;
		
		/* init camera */
		camera.transform.position.z = -.2f;
	}

	void update(float delta_time) override
	{

	}

	void render() override
	{		

	}
};