// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

namespace math { typedef struct vector4_t<float> vec4; }

template <>
struct reflect::Type<math::vec4>
{
    static const reflect::meta_t& meta();
    static const char* const name();
    static const reflect::properties_t& properties();
    static std::size_t size();

    static void from_string(const std::string& str, math::vec4& type);
    static std::string to_string(const math::vec4& type);
    static void from_json(const std::string& json, math::vec4& type);
    static std::string to_json(const math::vec4& type, const std::string& offset = "");
};