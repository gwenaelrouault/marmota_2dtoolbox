#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace marmot
{

    using SurfacePtr = std::shared_ptr<SDL_Surface>;

    using TexturePtr = std::shared_ptr<SDL_Texture>;

    inline TexturePtr make_texture(SDL_Texture *texture)
    {
        return TexturePtr(texture, SDL_DestroyTexture);
    }

    inline SurfacePtr make_surface(SDL_Surface *surface)
    {
        return SurfacePtr(surface, SDL_FreeSurface);
    }
}