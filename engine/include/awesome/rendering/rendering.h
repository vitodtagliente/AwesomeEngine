#pragma once

#include "primitives/mesh.h"
#include "renderer.h"

#ifdef INSTINCT_GL
#include "gl/gl.h"
#endif

#ifdef INSTINCT_DIRECTX
#include "directx/directx.h"
#endif

#ifdef INSTINCT_VULKAN
#include "vulkan/vulkan.h"
#endif