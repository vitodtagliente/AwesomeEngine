// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "game_tags.h"

const char* EnumType<GameTags>::name() { return "GameTags"; }
const enum_values_t& EnumType<GameTags>::values()
{
    static enum_values_t s_values{
        { "Bullet", static_cast<int>(GameTags::Bullet) }, 
        { "Minion", static_cast<int>(GameTags::Minion) }, 
        { "Player", static_cast<int>(GameTags::Player) }, 
    };
    return s_values;
}
