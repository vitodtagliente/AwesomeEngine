// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

struct NewSceneMenuItemType : RegisteredInTypeFactory<NewSceneMenuItemType>
{
    NewSceneMenuItemType();

    static const meta_t& meta();
    static const char* name();
    static class NewSceneMenuItem* const instantiate();
    static bool registered() { return value; };
};

