#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "application.h"
#include "utility/log.h"

#include "core/vertex_array_object.h"
#include "core/vertex_buffer_object.h"

#include "shading/shader.h"
#include "shading/program.h"
#include "shading/texture.h"

#include "primitives/triangle.h"
#include "primitives/cube.h"

#define DECLARE_MAIN(ApplicationDerivedType)				                        \
int main(int argc, const char ** argv)												\
{																					\
	Application* app = new ApplicationDerivedType();								\
	return execute_main(app);														\
} 

namespace Dreamkeeper
{
	int execute_main(Application* app);
	int desktop_device_main(Application* app);
	int mobile_device_main(Application* app);
}
