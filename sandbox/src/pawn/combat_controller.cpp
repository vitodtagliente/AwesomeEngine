#include "combat_controller.h"

#include <awesome/asset/asset_library.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture_library.h>

void CombatController::init()
{
	m_pawn = getOwner()->findComponent<Pawn>();
}

void CombatController::render(graphics::Renderer* const renderer)
{
	if (m_type != Type::Ranged)
		return;

	if (m_crosshair && m_crosshair->data.has_value())
	{
		const Sprite& data = m_crosshair->data.value();
		if (data.image)
		{
			std::shared_ptr<graphics::Texture> texture = graphics::TextureLibrary::instance().find(data.image->descriptor.id);
			if (texture)
			{
				renderer->drawSprite(texture.get(), m_crosshairTransform.matrix(), data.rect);
			}
		}
	}
}

void CombatController::update(const double deltaTime)
{
	const math::vec3 position = getOwner()->transform.position;
	const math::vec3 direction = m_pawn->getDirection();

	auto angle = std::atan2(direction.y, direction.x);
	m_crosshairTransform.position = position + math::vec3(
		std::cos(angle) * m_crosshairRadius,
		std::sin(angle) * m_crosshairRadius,
		0.f
	);

	m_crosshairTransform.update();
}

void CombatController::inspect()
{
	Component::inspect();
	editor::Layout::input("Type", m_type);
	editor::Layout::input("Crosshair", m_crosshair);
	editor::Layout::input("Crosshair Radius", m_crosshairRadius);
}

json::value CombatController::serialize() const
{
	json::value data = Component::serialize();
	data["type"] = enumToString(m_type);
	data["crosshair"] = m_crosshair ? ::serialize(m_crosshair->descriptor.id) : "";
	data["crosshairRadius"] = m_crosshairRadius;
	return data;
}

void CombatController::deserialize(const json::value& value)
{
	Component::deserialize(value);
	stringToEnum(value["type"].as_string(), m_type);

	uuid crosshairId = uuid::Invalid;
	::deserialize(value["crosshair"], crosshairId);
	m_crosshair = AssetLibrary::instance().find<SpriteAsset>(crosshairId);

	m_crosshairRadius = value["crosshairRadius"].as_number().as_float();
}

REFLECT_COMPONENT(CombatController)