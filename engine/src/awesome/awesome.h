#pragma once

#include "core/engine.h"
#include "core/event.h"
#include "core/platform.h"
#include "core/string.h"
#include "core/string_builder.h"
#include "core/string_id.h"
#include "core/types.h"
#include "core/io/file.h"
#include "core/io/directory.h"
#include "core/io/path.h"
#include "core/io/stream.h"
#include "core/io/stream_reader.h"
#include "core/io/stream_writer.h"
#include "core/io/string_reader.h"
#include "core/io/string_writer.h"

#include "application/application.h"
#include "application/input.h"
#include "application/time.h"
#include "application/window.h"

#include "data/color.h"
#include "data/image.h"
#include "data/ini.h"
#include "data/timer.h"

#include "graphics/graphics_module.h"
#include "graphics/graphics_api.h"
#include "graphics/renderable.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "graphics/shader_program.h"
#include "graphics/mesh/mesh.h"
#include "graphics/mesh/quad.h"
#include "graphics/render_command.h"
#include "graphics/material.h"
#include "graphics/components/sprite_component.h"
#include "graphics/components/mesh_component.h"
#include "graphics/material_library.h"
#include "graphics/texture_library.h"
#include "graphics/shaders.h"

#include "math/math.h"
#include "math/matrix.h"
#include "math/vector.h"
#include "math/quaternion.h"
#include "math/transform.h"
#include "math/rectangle.h"

#include "scene/component.h"
#include "scene/object.h"
#include "scene/world.h"

#include "services/localization/localization.h"