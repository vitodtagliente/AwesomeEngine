// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

struct GameModeType : RegisteredInTypeFactory<GameModeType>
{
    GameModeType() = delete;

    static const TypeDefinition& type();
    static bool registered() { return value; };
};
