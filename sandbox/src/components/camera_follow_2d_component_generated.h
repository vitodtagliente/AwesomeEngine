// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

struct CameraFollow2dComponentType : RegisteredInTypeFactory<CameraFollow2dComponentType>
{
    CameraFollow2dComponentType();

    static const meta_t& meta();
    static const char* name();
    static class CameraFollow2dComponent* const instantiate();
    static bool registered() { return value; };
};

