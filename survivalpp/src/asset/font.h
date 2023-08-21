#pragma once

#include <filesystem>

#include <SDL3/SDL_ttf.h>

#include "asset/asset.h"

class Font : public Asset
{
public:
    Font() = default;
    Font(const std::filesystem::path& path);
    ~Font();

    inline TTF_Font* const data() const { return m_data; }

    inline operator bool() const
    {
        return m_data != nullptr;
    }

    void free();

private:
    TTF_Font* m_data{ nullptr };
};