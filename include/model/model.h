#pragma once

#include <string>
#include <vector>
#include "sprite.h"

namespace marmot
{
    class Model
    {
    public:
        Model() {}
        virtual ~Model() {}

        std::vector<Sprite>& get_sprites();

    private:
        std::vector<Sprite> _sprites;
    };
}