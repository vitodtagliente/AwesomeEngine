#pragma once

#include "minimal.h"
#include "rendering.h"
#include "windowing/window.h"

#define DECLARE_MAIN(ApplicationDerivedType)				\
int main(int argc, const char ** argv)						\
{															\
	Application::run<ApplicationDerivedType>();				\
} 
