// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

struct HealthComponentType : RegisteredInTypeFactory<HealthComponentType>
{
    HealthComponentType();

    static const meta_t& meta();
    static const char* name();
    static class HealthComponent* const instantiate();
    static bool registered() { return value; };
};

