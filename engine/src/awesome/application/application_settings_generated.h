// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct EnumType<enum class ApplicationMode>
{
    static const char* name();
    static const std::map<const char*, int> values();
};

template <>
struct EnumType<enum class FpsMode>
{
    static const char* name();
    static const std::map<const char*, int> values();
};

struct ApplicationSettingsType
{
    ApplicationSettingsType();

    static const meta_t& meta();
    static const char* name();
    static class ApplicationSettings* const instantiate();
};
extern ApplicationSettingsType __applicationsettings_type;
