#include "combat_controller.h"

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/asset/asset_library.h>
#include <awesome/components/camera.h>
#include <awesome/components/sprite_animator.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture_library.h>

#include "bullet.h"

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

void CombatController::update(const double /*deltaTime*/)
{
	const math::vec3 position = getOwner()->transform.position;
	m_direction = m_pawn->getDirection();

	Input& input = Input::instance();
	Canvas& canvas = Canvas::instance();
	if (input.isMousePositionValid())
	{
		const float width = static_cast<float>(canvas.getWidth());
		const float height = static_cast<float>(canvas.getHeight());
		const math::vec2& mousePosition = input.getMousePosition();
		m_direction = math::vec3(
			2 * (mousePosition.x / width) - 1.0, 
			2 * (-mousePosition.y / height) + 1.0f, 
			0.f
		).normalize();
	}

	auto angle = std::atan2(m_direction.y, m_direction.x);
	m_crosshairTransform.position = position + math::vec3(
		std::cos(angle) * m_crosshairRadius,
		std::sin(angle) * m_crosshairRadius,
		1.5f
	);

	m_crosshairTransform.update();
}

void CombatController::attack()
{
	if (m_type == Type::Ranged)
	{
		Entity* const entity = World::instance().spawn(m_bulletPrefab, m_crosshairTransform.position);
		Bullet* const bullet = entity->findComponent<Bullet>();
		if (bullet)
		{
			bullet->shoot(m_direction);
		}
	}
	else
	{
		SpriteAnimator* const animator = getOwner()->findComponent<SpriteAnimator>();
		if (animator) animator->play("attack");
	}
}

void CombatController::inspect()
{
	Component::inspect();
	editor::Layout::input("Type", m_type);
	editor::Layout::input("Bullet Prefab", m_bulletPrefab);
	editor::Layout::input("Crosshair", m_crosshair);
	editor::Layout::input("Crosshair Radius", m_crosshairRadius);
}

json::value CombatController::serialize() const
{
	json::value data = Component::serialize();
	data["type"] = enumToString(m_type);
	data["bulletPrefab"] = m_bulletPrefab ? ::serialize(m_bulletPrefab->descriptor.id) : "";
	data["crosshair"] = m_crosshair ? ::serialize(m_crosshair->descriptor.id) : "";
	data["crosshairRadius"] = m_crosshairRadius;
	return data;
}

void CombatController::deserialize(const json::value& value)
{
	Component::deserialize(value);
	stringToEnum(value.safeAt("type").as_string(""), m_type);

	uuid bulletId = uuid::Invalid;
	::deserialize(value.safeAt("bulletPrefab"), bulletId);
	m_bulletPrefab = AssetLibrary::instance().find<PrefabAsset>(bulletId);

	uuid crosshairId = uuid::Invalid;
	::deserialize(value.safeAt("crosshair"), crosshairId);
	m_crosshair = AssetLibrary::instance().find<SpriteAsset>(crosshairId);

	m_crosshairRadius = value.safeAt("crosshairRadius").as_number(1.f).as_float();
}

REFLECT_COMPONENT(CombatController)