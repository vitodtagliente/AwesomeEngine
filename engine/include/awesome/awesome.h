#pragma once

#include "ai/ai.h"
#include "assets/assets.h"
#include "audio/audio.h"
#include "math/math.h"
#include "networking/networking.h"
#include "physics/physics.h"
#include "rendering/rendering.h"
#include "physics/physics.h"
#include "scenegraph/scenegraph.h"
#include "utility/utility.h"
#include "windowing/windowing.h"

#include "application.h"

#define DECLARE_MAIN(ApplicationDerivedType)				\
int main(int argc, const char ** argv)						\
{															\
	Application::run<ApplicationDerivedType>();				\
} 
