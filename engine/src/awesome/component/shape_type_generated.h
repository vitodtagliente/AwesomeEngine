// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct EnumType<enum class ShapeType>
{
    static const char* name();
    static const  enum_values_t& values();
};

struct __ShapeTypeEnum : RegisteredInEnumFactory<enum class ShapeType>
{
    static bool registered() { return value; };
};

