#include "button_component.h"

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_library.h>
#include <awesome/entity/entity.h>

void ButtonComponent::render(graphics::Renderer2D* const renderer)
{
	if (m_image == nullptr || m_image->state != Asset::State::Ready) return;
	
	std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(m_image->descriptor.id);
	if (texture != nullptr)
	{
		graphics::Color currentColor = m_normalColor;
		if (!m_clickTimer.isExpired())
		{
			currentColor = m_clickColor;
		}
		else if (m_isHovered)
		{
			currentColor = m_hoveredColor;
		}
		renderer->drawTexture(texture.get(), getOwner()->transform.matrix(), m_rect, currentColor);
	}
}

void ButtonComponent::update(const double deltaTime)
{
	m_clickTimer.tick(deltaTime);

	Canvas& canvas = Canvas::instance();
	Input& input = Input::instance();

	math::vec2 normalizedMousePosition(
		(input.getMousePosition().x / static_cast<float>(canvas.getWidth()) - 0.5f) * 2.0f,  // [-1,1]
		-(input.getMousePosition().y / static_cast<float>(canvas.getHeight()) - 0.5f) * 2.0f // [-1,1]
	);

	const auto& position = getOwner()->transform.position;
	const auto& size = getOwner()->transform.scale;

	m_isHovered = normalizedMousePosition.x >= position.x - size.x && normalizedMousePosition.x <= position.x + size.x
		&& normalizedMousePosition.y > position.y - size.y && normalizedMousePosition.y < position.y + size.y;
	if (m_isHovered && input.consumeKeyPressed(KeyCode::MouseLeftButton))
	{
		m_clickTimer.reset();
	}
}