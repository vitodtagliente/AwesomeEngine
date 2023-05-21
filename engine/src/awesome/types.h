/// Copyright (c) Vito Domenico Tagliente
#pragma once

// Force the types registration from a static library

// assets
#include "asset/audio_asset.h"
#include "asset/image_asset.h"
#include "asset/prefab_asset.h"
#include "asset/scene_asset.h"
#include "asset/sprite_animation_asset.h"
#include "asset/user_interface_asset.h"
#include "asset/widget_asset.h"
// components
#include "components/audio_listener_component.h"
#include "components/audio_source_component.h"
#include "components/rigidbody2d_component.h"
#include "components/camera_component.h"
#include "components/camera_controller2d_component.h"
#include "components/camera_follow2d_component.h"
#include "components/collider2d_component.h"
#include "components/lifetime_component.h"
#include "components/orthographic_camera_component.h"
#include "components/sprite_animator_component.h"
#include "components/sprite_renderer_component.h"
// editor
#include "editor/windows/asset_inspector_window.h"
#include "editor/windows/content_browser_window.h"
#include "editor/windows/entity_inspector_window.h"
#include "editor/windows/scene_window.h"