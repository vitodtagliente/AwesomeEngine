#include "crosshair_component.h"

#include <awesome/application/input.h>
#include <awesome/component/camera_component.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void CrosshairComponent::init()
{
	getOwner()->transform.scale = _minScale;
}

void CrosshairComponent::update(const double deltaTime)
{
	// scale animation
	math::vec3& scale = getOwner()->transform.scale;
	scale = math::vec3(
		scale.x + (_scaleUp ? 1.f : -1.f) * _scaleSpeed * static_cast<float>(deltaTime),
		scale.y + (_scaleUp ? 1.f : -1.f) * _scaleSpeed * static_cast<float>(deltaTime),
		0.f
	);

	if (scale.x <= _minScale.x || scale.x >= _maxScale.x)
	{
		_scaleUp = !_scaleUp;
	}

	Input& input = Input::instance();
	CameraComponent* const camera = CameraComponent::main();
	if (input.isMousePositionValid() && camera)
	{
		getOwner()->transform.position = camera->screenToWorldCoords(input.getMousePosition());
		getOwner()->transform.position.z;
	}
}

void CrosshairComponent::inspect()
{
	Component::inspect();
	Layout::input("Min Scale", _minScale);
	Layout::input("Max Scale", _maxScale);
	Layout::input("Scale Speed", _scaleSpeed);
}

json::value CrosshairComponent::serialize() const
{
	json::value data = Component::serialize();
	data["minScale"] = ::serialize(_minScale);
	data["maxScale"] = ::serialize(_maxScale);
	data["scaleSpeed"] = _scaleSpeed;
	return data;
}

void CrosshairComponent::deserialize(const json::value& data)
{
	Component::deserialize(data);
	::deserialize(data.safeAt("minScale"), _minScale);
	::deserialize(data.safeAt("maxScale"), _maxScale);
	_scaleSpeed = data.safeAt("scaleSpeed").as_number(1.f).as_float();
}