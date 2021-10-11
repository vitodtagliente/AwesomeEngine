/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>

namespace editor
{
	class Context;
}

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

	void update(class World& world, double deltaTime) override;
	void inspect(editor::Context& context) override;
};