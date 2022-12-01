// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct EnumType<enum class SpawnType>
{
    static const char* name();
    static const std::map<const char*, int> values();
};

struct WaveType : RegisteredInTypeFactory<WaveType>
{
    WaveType() = delete;

    static const Type& type();
    static bool registered() { return value; };
};
