#pragma once

#include "application.h"
#include "component.h"
#include "object.h"
#include "windowing/window.h"

#define DECLARE_MAIN(ApplicationDerivedType)				\
int main(int argc, const char ** argv)						\
{															\
	Application::run<ApplicationDerivedType>();				\
} 
