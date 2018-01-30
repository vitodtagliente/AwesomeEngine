#pragma once 

#include <awesome/awesome.h>
#include <cmath>
#include <glad/glad.h>

using namespace Awesome;

class TestApplication : public Application
{
public:
	float color[4]{ 1.0f, 0.0f,0.0f,1.0f };

	void init() override {
		//setTitle("AwesomeEngine: ColorApplication");
	}
	
	void update(float deltaTime) override {
		color[0] = sin(deltaTime) * 0.5f + 0.5f;
		color[1] = cos(deltaTime) * 0.5f + 0.5f;
	}

	void render() override {
		glClearBufferfv(GL_COLOR, 0, color);
	}
};