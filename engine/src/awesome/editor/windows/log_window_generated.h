// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

struct LogWindowType : RegisteredInTypeFactory<LogWindowType>
{
    LogWindowType();

    static const meta_t& meta();
    static const char* name();
    static class LogWindow* const instantiate();
    static bool registered() { return value; };
};

