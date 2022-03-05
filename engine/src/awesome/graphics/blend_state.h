/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "color.h"

namespace graphics
{
    enum class Blend
    {
        Zero,
        One,
        SourceAlpha,
        InverseSourceAlpha,
        DestinationAlpha,
        InverseDestinationAlpha,
        SourceColor,
        InverseSourceColor,
        DestinationColor,
        InverseDestinationColor,
        BlendFactor,
        InverseBlendFactor
    };

    enum class BlendFunction
    {
        Add,
        Subtract,
        ReverseSubtract,
        Minimum,
        Maximum
    };

    struct BlendState
    {
        bool isBlendEnabled;
        Blend sourceColorBlend;
        Blend destinationColorBlend;
        BlendFunction colorBlendFunction;
        Blend sourceAlphaBlend;
        Blend destinationAlphaBlend;
        BlendFunction alphaBlendFunction;
        Color blendFactor;
    };
}