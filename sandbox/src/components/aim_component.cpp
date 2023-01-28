#include "aim_component.h"

#include <awesome/application/input.h>
#include <awesome/component/camera_component.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture_library.h>

void AimComponent::render(graphics::Renderer* const renderer)
{
	if (!m_visible
		|| m_image == nullptr
		|| m_image->state != Asset::State::Ready) return;

	std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(m_image->id);
	if (texture != nullptr)
	{
		math::transform transform = getOwner()->transform;
		transform.position = m_position;
		transform.scale.x = transform.scale.y = m_size;
		transform.update();
		renderer->submitDrawTexture(texture.get(), transform.matrix(), m_rect, graphics::Color::White);
	}
}

void AimComponent::update(const double deltaTime)
{
	Input& input = Input::instance();
	CameraComponent* const camera = CameraComponent::main();
	if (camera == nullptr) return;

	m_visible = input.isMousePositionValid();
	const math::vec3 inputPosition = camera->screenToWorldCoords(input.getMousePosition());
	m_direction = (inputPosition - getOwner()->transform.position).normalize();
	const float distance = inputPosition.distance(getOwner()->transform.position);
	m_range = math::clamp(distance, m_minRange, m_maxRange);
	m_position = getOwner()->transform.position + m_direction * m_range;

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