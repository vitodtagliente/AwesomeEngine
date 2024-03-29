// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

namespace math { typedef struct rectangle_t<float> rect; }

template <>
struct reflect::Type<math::rect>
{
    static const reflect::meta_t& meta();
    static const char* const name();
    static const reflect::properties_t& properties();
    static std::size_t size();

    static void from_string(const std::string& str, math::rect& type);
    static std::string to_string(const math::rect& type);
    static void from_json(const std::string& json, math::rect& type);
    static std::string to_json(const math::rect& type, const std::string& offset = "");
};