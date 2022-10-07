// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "performance_window.h"

const meta_t& PerformanceWindow::getTypeMeta() const { return PerformanceWindowType::type().meta; }
const std::string& PerformanceWindow::getTypeName() const { return PerformanceWindowType::type().name; }
const properties_t PerformanceWindow::getTypeProperties() const {
    properties_t properties = Window::getTypeProperties();
    return properties;
}
std::size_t PerformanceWindow::getTypeSize() const { return PerformanceWindowType::type().size; }

const Type& PerformanceWindowType::type()
{
    static const Type s_type([]() -> IType* { return new PerformanceWindow(); }, "PerformanceWindow", {
        std::make_pair("Category", "Window"),
    }, sizeof(PerformanceWindow));
    return s_type;
}
