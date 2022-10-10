// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "shape_type.h"

const char* EnumType<ShapeType>::name() { return "ShapeType"; }
const std::map<const char*, int>  EnumType<ShapeType>::values()
{
    static std::map<const char*, int> s_values{
        { "None", static_cast<int>(ShapeType::None) }, 
        { "Circle", static_cast<int>(ShapeType::Circle) }, 
        { "Rect", static_cast<int>(ShapeType::Rect) }, 
    };
    return s_values;
}

