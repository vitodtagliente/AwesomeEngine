/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "camera_component.h"

#include "orthographic_camera_component_generated.h"

CLASS(Category = Component)
class OrthographicCameraComponent : public CameraComponent
{
public:
	OrthographicCameraComponent();
	virtual ~OrthographicCameraComponent() = default;

	void update(double deltaTime) override;

	virtual void inspect() override;

	PROPERTY() float nearPlane{ -30.f };
	PROPERTY() float farPlane{ 1000.f };
	PROPERTY() bool pixelPerfect{ true };
	PROPERTY() int pixelsPerUnit{ 32 };

	GENERATED_BODY()
};