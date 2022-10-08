#include "orthographic_camera_component.h"

OrthographicCameraComponent::OrthographicCameraComponent()
	: CameraComponent()
{
	m_data = std::make_unique<graphics::OrthographicCamera>();
}

void OrthographicCameraComponent::update(const double deltaTime)
{
	if (graphics::OrthographicCamera* const data = dynamic_cast<graphics::OrthographicCamera*>(m_data.get()))
	{
		data->farPlane = farPlane;
		data->nearPlane = nearPlane;
		data->pixelPerfect = pixelPerfect;
		data->pixelsPerUnit = pixelsPerUnit;
	}
	CameraComponent::update(deltaTime);
}