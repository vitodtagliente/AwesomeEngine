// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "net_mode.h"

const char* EnumType<NetMode>::name() { return "NetMode"; }
const enum_values_t& EnumType<NetMode>::values()
{
    static enum_values_t s_values{
        { "Client", static_cast<int>(NetMode::Client) }, 
        { "Shared", static_cast<int>(NetMode::Shared) }, 
        { "Server", static_cast<int>(NetMode::Server) }, 
    };
    return s_values;
}

