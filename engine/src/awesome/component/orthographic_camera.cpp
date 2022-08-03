#include "orthographic_camera.h"

#include <awesome/editor/layout.h>

namespace component
{
	OrthographicCamera::OrthographicCamera()
		: Camera()
	{
		m_data = std::make_unique<graphics::OrthographicCamera>();
	}

	void OrthographicCamera::update(const double deltaTime)
	{
		if (graphics::OrthographicCamera* const data = dynamic_cast<graphics::OrthographicCamera*>(m_data.get()))
		{
			data->farPlane = farPlane;
			data->nearPlane = nearPlane;
			data->pixelPerfect = pixelPerfect;
			data->pixelsPerUnit = pixelsPerUnit;
		}
		Camera::update(deltaTime);
	}

	json::value OrthographicCamera::serialize() const
	{
		json::value data = Camera::serialize();
		data["nearPlane"] = nearPlane;
		data["farPlane"] = farPlane;
		data["pixelPerfect"] = pixelPerfect;
		data["pixelsPerUnit"] = pixelsPerUnit;
		return data;
	}

	void OrthographicCamera::deserialize(const json::value& value)
	{
		Camera::deserialize(value);
		nearPlane = value["nearPlane"].as_number(-30.f).as_float();
		farPlane = value["farPlane"].as_number(1000.f).as_float();
		pixelPerfect = value["pixelPerfect"].as_bool(true);
		pixelsPerUnit = value["pixelsPerUnit"].as_number(32).as_int();
	}

	void OrthographicCamera::inspect()
	{
		Camera::inspect();
		editor::Layout::input("Near Plane", nearPlane);
		editor::Layout::input("Far Plane", farPlane);
		editor::Layout::input("Pixel Perfect", pixelPerfect);
		editor::Layout::input("Pixel per unit", pixelsPerUnit);
	}
}