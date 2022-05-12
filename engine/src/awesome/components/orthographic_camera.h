/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "camera.h"

namespace graphics
{
	class Renderer;
	class Texture;
}

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera() = default;
	virtual ~OrthographicCamera() = default;

	void update(double deltaTime) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	REFLECT()

	float nearPlane{ -30.f };
	float farPlane{ 1000.f };
	bool pixelPerfect{ true };
	int pixelsPerUnit{ 32 };

protected:
	virtual math::matrix4 computeProjectionMatrix() override;
};