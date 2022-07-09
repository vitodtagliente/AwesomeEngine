#include "components_loader.h"

#include <awesome/core/reflection.h>

#include <awesome/component/body2d.h>
#include <awesome/component/camera.h>
#include <awesome/component/camera_controller_2d.h>
#include <awesome/component/collider2d.h>
#include <awesome/component/gizmos_renderer.h>
#include <awesome/component/orthographic_camera.h>
#include <awesome/component/sprite_animator.h>
#include <awesome/component/sprite_renderer.h>

void ComponentsLoader::load()
{
	TypeFactory::load<component::Body2d>();
	TypeFactory::load<component::Camera>();
	TypeFactory::load<component::CameraController2d>();
	TypeFactory::load<component::Collider2d>();
	TypeFactory::load<component::GizmosRenderer>();
	TypeFactory::load<component::OrthographicCamera>();
	TypeFactory::load<component::SpriteAnimator>();
	TypeFactory::load<component::SpriteRenderer>();
}