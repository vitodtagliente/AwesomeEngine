/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <SDL3/SDL.h>

#include "color.h"

namespace graphics
{
    class Texture
    {
    public:
        Texture() = default;
        Texture(const std::filesystem::path& path);
        ~Texture();

        inline SDL_Texture* const data() const { return m_data; }
        inline int width() const { return m_width; }
        inline int height() const { return m_height; }

        inline operator bool() const
        {
            return m_data != nullptr;
        }

        void free();

    private:
        SDL_Texture* m_data{ nullptr };
        int m_width{ 0 };
        int m_height{ 0 };
    };
}