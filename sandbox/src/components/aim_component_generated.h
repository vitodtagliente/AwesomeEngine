// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct reflect::Type<class AimComponent> : reflect::RegisteredInTypeFactory<class AimComponent>
{
    static IType* const instantiate();
    static const reflect::meta_t& meta();
    static const char* const name();
    static const reflect::properties_t& properties();
    static std::size_t size();

    static void from_string(const std::string& str, AimComponent& type);
    static std::string to_string(const AimComponent& type);
    static void from_json(const std::string& json, AimComponent& type);
    static std::string to_json(const AimComponent& type, const std::string& offset = "");

    static bool registered() { return type_registered; };
};