/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "camera_component.h"

#include "orthographic_camera_component_generated.h"

CLASS(Type = Component)
class OrthographicCameraComponent : public CameraComponent
{
public:
	PROPERTY() float nearPlane{ -30.f };
	PROPERTY() float farPlane{ 1000.f };
	PROPERTY() bool pixelPerfect{ true };
	PROPERTY() int pixelsPerUnit{ 32 };

	GENERATED_BODY()

private:
	virtual math::mat4 computeProjectionMatrix() const override;
};