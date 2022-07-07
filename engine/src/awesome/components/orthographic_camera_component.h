/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "camera_component.h"

class OrthographicCameraComponent : public CameraComponent
{
public:
	OrthographicCameraComponent();
	virtual ~OrthographicCameraComponent() = default;

	void update(double deltaTime) override;

	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;
	virtual void inspect() override;

	REFLECT()

	float nearPlane{ -30.f };
	float farPlane{ 1000.f };
	bool pixelPerfect{ true };
	int pixelsPerUnit{ 32 };

};