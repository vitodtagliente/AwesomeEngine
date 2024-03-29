// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include "core/singleton.h"

enum class FpsMode : int
{
    Fps30 = 30,
    Fps60 = 60,
    Fps120 = 120,
    Fps240 = 240,
    Unlimited,
};

struct EngineSettings : public Singleton<EngineSettings>
{
    FpsMode fps { FpsMode::Fps120 };
};
