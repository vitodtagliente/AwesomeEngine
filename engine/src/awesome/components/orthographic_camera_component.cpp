#include "orthographic_camera_component.h"

#include <awesome/engine/canvas.h>
#include <awesome/graphics/camera.h>

math::mat4 OrthographicCameraComponent::computeProjectionMatrix() const
{
	const auto& canvas = Canvas::instance();
	int screenWidth = canvas.getWidth();
	int screenHeight = canvas.getHeight();
	if (pixelPerfect)
	{
		screenWidth /= pixelsPerUnit;
		screenHeight /= pixelsPerUnit;
	}

	return graphics::Camera::ortho(nearPlane, farPlane, screenWidth, screenHeight, 1.0f);
}
