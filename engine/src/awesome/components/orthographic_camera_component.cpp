#include "orthographic_camera_component.h"

#include <awesome/application/canvas.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/context.h>
#include <awesome/graphics/renderer.h>
#include <awesome/math/matrix4.h>

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

json::value OrthographicCameraComponent::serialize() const
{
	json::value data = CameraComponent::serialize();
	data["nearPlane"] = nearPlane;
	data["farPlane"] = farPlane;
	data["pixelPerfect"] = pixelPerfect;
	data["pixelsPerUnit"] = pixelsPerUnit;
	return data;
}

void OrthographicCameraComponent::deserialize(const json::value& value)
{
	CameraComponent::deserialize(value);
	nearPlane = value["nearPlane"].as_number(-30.f).as_float();
	farPlane = value["farPlane"].as_number(1000.f).as_float();
	pixelPerfect = value["pixelPerfect"].as_bool(true);
	pixelsPerUnit = value["pixelsPerUnit"].as_number(32).as_int();
}

void OrthographicCameraComponent::inspect()
{
	CameraComponent::inspect();
	editor::Layout::input("Near Plane", nearPlane);
	editor::Layout::input("Far Plane", farPlane);
	editor::Layout::input("Pixel Perfect", pixelPerfect);
	editor::Layout::input("Pixel per unit", pixelsPerUnit);
}

REFLECT_COMPONENT(OrthographicCameraComponent)