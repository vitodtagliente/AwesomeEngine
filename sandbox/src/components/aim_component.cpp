#include "aim_component.h"

#include <awesome/engine/input.h>
#include <awesome/components/camera_component.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>

void AimComponent::render(graphics::Renderer& renderer)
{
	if (!m_image.ready())
	{
		m_image.load();
		return;
	}

	std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(m_image);
	if (texture != nullptr)
	{
		math::transform transform = getOwnerTransform();
		transform.position = m_position;
		transform.scale.x = transform.scale.y = m_size;
		transform.update();
		renderer.submitDrawTexture(texture.get(), getOwnerTransform().matrix(), m_rect, graphics::Color::White);
	}
}

void AimComponent::update(const double deltaTime)
{
	Input& input = Input::instance();
	CameraComponent* const camera = CameraComponent::main();
	if (camera == nullptr) return;

	m_visible = input.isMousePositionValid();
	const math::vec3 inputPosition = camera->screenToWorldCoords(input.getMousePosition());
	m_direction = (inputPosition - getOwnerTransform().position).normalize();
	const float distance = inputPosition.distance(getOwnerTransform().position);
	m_range = math::clamp(distance, m_minRange, m_maxRange);
	m_position = getOwnerTransform().position + m_direction * m_range;

	m_size = math::clamp(m_size + m_resizeSpeed * static_cast<float>(deltaTime) * (m_reduceSize ? -1.f : 1.f), m_minSize, m_maxSize);
	if (m_reduceSize && m_size == m_minSize)
	{
		m_reduceSize = false;
	}
	else if (m_reduceSize == false && m_size == m_maxSize)
	{
		m_reduceSize = true;
	}
}