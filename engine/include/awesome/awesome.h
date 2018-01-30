#pragma once

#include "ai/ai.h"
#include "assets/assets.h"
#include "audio/audio.h"
#include "networking/networking.h"
#include "physics/physics.h"
#include "rendering/rendering.h"
#include "physics/physics.h"
#include "utility/utility.h"
#include "windowing/windowing.h"

#include "application.h"

#define DECLARE_MAIN(ApplicationDerivedType)				                        \
int main(int argc, const char ** argv)												\
{																					\
	Application* app = new ApplicationDerivedType();								\
	return execute_main(app);														\
} 

namespace Awesome
{
	int execute_main(Application* app);
	int desktop_device_main(Application* app);
	int mobile_device_main(Application* app);
}
