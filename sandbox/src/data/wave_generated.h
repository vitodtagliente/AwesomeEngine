// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct EnumType<enum class SpawnType>
{
    static const char* name();
    static const  enum_values_t& values();
};

struct SpawnTypeEnum : RegisteredInEnumFactory<enum class SpawnType>
{
    static bool registered() { return value; };
};

struct WaveType : RegisteredInTypeFactory<WaveType>
{
    WaveType() = delete;

    static const TypeDefinition& type();
    static bool registered() { return value; };
};

