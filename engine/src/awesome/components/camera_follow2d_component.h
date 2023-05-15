/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/component.h>

#include "camera_follow2d_component_generated.h"

CLASS(Type = Component)
class CameraFollow2dComponent : public Component
{
public:
	virtual void init() override;
	virtual void update(double deltaTime) override;

	GENERATED_BODY()

private:
	class OrthographicCameraComponent* m_ortho{ nullptr };
	PROPERTY() float m_speed{ 1.0f };
	class Entity* m_target{ nullptr };
	PROPERTY() std::string m_targetTag;
};