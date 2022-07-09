#include "components_loader.h"

#include <awesome/core/reflection.h>

#include <awesome/components/body2d.h>
#include <awesome/components/camera.h>
#include <awesome/components/camera_controller_2d.h>
#include <awesome/components/collider2d.h>
#include <awesome/components/gizmos_renderer.h>
#include <awesome/components/orthographic_camera.h>
#include <awesome/components/sprite_animator.h>
#include <awesome/components/sprite_renderer.h>

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