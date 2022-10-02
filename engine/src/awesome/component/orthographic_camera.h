/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "base_camera.h"

#include "orthographic_camera_generated.h"

CLASS()
class OrthographicCamera : public BaseCamera
{
public:
	OrthographicCamera();
	virtual ~OrthographicCamera() = default;

	void update(double deltaTime) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	PROPERTY() float nearPlane{ -30.f };
	PROPERTY() float farPlane{ 1000.f };
	PROPERTY() bool pixelPerfect{ true };
	PROPERTY() int pixelsPerUnit{ 32 };

	GENERATED_BODY()
};