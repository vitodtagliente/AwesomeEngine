#pragma once

#include "application.h"
#include "component.h"
#include "object.h"
#include "rendering/components/mesh_rendering_component.h"
#include "rendering/primitives/primitives.h"
#include "rendering/primitives/triangle.h"
#include "windowing/window.h"

#define DECLARE_MAIN(ApplicationDerivedType)				\
int main(int argc, const char ** argv)						\
{															\
	Application::run<ApplicationDerivedType>();				\
} 
