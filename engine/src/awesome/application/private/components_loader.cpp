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
	TypeFactory::load<Body2d>();
	TypeFactory::load<component::Camera>();
	TypeFactory::load<CameraController2d>();
	TypeFactory::load<Collider2d>();
	TypeFactory::load<GizmosRenderer>();
	TypeFactory::load<component::OrthographicCamera>();
	TypeFactory::load<SpriteAnimator>();
	TypeFactory::load<SpriteRenderer>();
}