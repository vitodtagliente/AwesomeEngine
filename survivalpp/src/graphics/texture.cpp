#include "texture.h"

#include <SDL3/SDL_image.h>

extern SDL_Renderer* sdl_renderer;

namespace graphics
{
    Texture::Texture(const std::filesystem::path& path)
    {
        SDL_Surface* img = IMG_Load(path.string().c_str());
        if (img == nullptr)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.string().c_str(), IMG_GetError());
        }
        else
        {
            //Create texture from surface pixels
            m_data = SDL_CreateTextureFromSurface(sdl_renderer, img);
            m_width = img->w;
            m_height = img->h;

            SDL_DestroySurface(img);
        }
    }

    Texture::~Texture()
    {
        free();
    }

    void Texture::free()
    {
        if (m_data != nullptr)
        {
            SDL_DestroyTexture(m_data);
            m_data = NULL;
            m_width = 0;
            m_height = 0;
        }
    }
}
