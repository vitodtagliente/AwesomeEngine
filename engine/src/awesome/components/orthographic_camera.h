/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/entity/component.h>

namespace graphics
{
	class Renderer;
	class Texture;
}

class OrthographicCamera : public Component
{
public:
	OrthographicCamera();

	float nearPlane;
	float farPlane;
	bool pixelPerfect;
	int pixelsPerUnit;

	void update(double deltaTime) override;

	REFLECT()
};