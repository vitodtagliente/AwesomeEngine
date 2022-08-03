#include "components_loader.h"

#include <awesome/component/body2d.h>
#include <awesome/component/camera.h>
#include <awesome/component/camera_controller_2d.h>
#include <awesome/component/collider2d.h>
#include <awesome/component/gizmos_renderer.h>
#include <awesome/component/orthographic_camera.h>
#include <awesome/component/particles2d.h>
#include <awesome/component/sprite_animator.h>
#include <awesome/component/sprite_renderer.h>

void ComponentsLoader::load()
{
	component::Body2d::autoload();
	component::Camera::autoload();
	component::CameraController2d::autoload();
	component::Collider2d::autoload();
	component::GizmosRenderer::autoload();
	component::OrthographicCamera::autoload();
	component::Particles2d::autoload();
	component::SpriteAnimator::autoload();
	component::SpriteRenderer::autoload();
}