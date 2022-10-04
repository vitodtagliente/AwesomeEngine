#include "combat_controller_component.h"

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/asset/asset_library.h>
#include <awesome/component/camera_component.h>
#include <awesome/component/sprite_animator_component.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/renderer.h>
#include <awesome/graphics/texture_library.h>

#include "bullet_component.h"

void CombatControllerComponent::init()
{
	m_pawn = getOwner()->findComponent<PawnComponent>();
}

void CombatControllerComponent::render(graphics::Renderer2D* const renderer)
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
				renderer->drawTexture(texture.get(), m_crosshairTransform.matrix(), data.rect);
			}
		}
	}
}

void CombatControllerComponent::update(const double /*deltaTime*/)
{
	math::vec3& position = getOwner()->transform.position;
	m_direction = m_pawn->getDirection();

	Input& input = Input::instance();
	CameraComponent* const camera = CameraComponent::main();
	if (input.isMousePositionValid() && camera)
	{
		m_direction = (camera->screenToWorldCoords(input.getMousePosition()) - position).normalize();
		if (input.isKeyPressed(KeyCode::MouseWheelButton))
		{
			position = camera->screenToWorldCoords(input.getMousePosition());
		}
	}

	auto angle = std::atan2(m_direction.y, m_direction.x);
	m_crosshairTransform.position = position + math::vec3(
		std::cos(angle) * m_crosshairRadius,
		std::sin(angle) * m_crosshairRadius,
		1.5f
	);

	m_crosshairTransform.update();
}

void CombatControllerComponent::attack()
{
	if (m_type == Type::Ranged)
	{
		Entity* const entity = World::instance().spawn(m_bulletPrefab, m_crosshairTransform.position);
		BulletComponent* const bullet = entity->findComponent<BulletComponent>();
		if (bullet)
		{
			bullet->shoot(m_direction);
		}
	}
	else
	{
		SpriteAnimatorComponent* const animator = getOwner()->findComponent<SpriteAnimatorComponent>();
		if (animator) animator->play("attack");
	}
}

void CombatControllerComponent::inspect()
{
	Component::inspect();
	Layout::input("Type", m_type);
	Layout::input("Bullet Prefab", m_bulletPrefab);
	Layout::input("Crosshair", m_crosshair);
	Layout::input("Crosshair Radius", m_crosshairRadius);
}

json::value CombatControllerComponent::serialize() const
{
	json::value data = Component::serialize();
	data["type"] = enumToString(m_type);
	data["bulletPrefab"] = m_bulletPrefab ? ::serialize(m_bulletPrefab->descriptor.id) : "";
	data["crosshair"] = m_crosshair ? ::serialize(m_crosshair->descriptor.id) : "";
	data["crosshairRadius"] = m_crosshairRadius;
	return data;
}

void CombatControllerComponent::deserialize(const json::value& value)
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