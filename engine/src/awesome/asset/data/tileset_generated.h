// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

struct TileType : RegisteredInTypeFactory<TileType>
{
    TileType() = delete;

    static const TypeDefinition& type();
    static bool registered() { return value; };
};

struct TilesetType : RegisteredInTypeFactory<TilesetType>
{
    TilesetType() = delete;

    static const TypeDefinition& type();
    static bool registered() { return value; };
};

