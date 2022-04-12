/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtreflect/reflect.h>

using namespace reflect;

#define REFLECT_COMPONENT(T) REFLECT_IMP_CATEGORY(T, Component)
#define REFLECT_EDITOR(T) REFLECT_IMP_CATEGORY(T, Editor)