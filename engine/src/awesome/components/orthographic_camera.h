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

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	REFLECT()
};