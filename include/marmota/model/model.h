#pragma once

#include <string>
#include <vector>
#include "sprite.h"

namespace marmot::marmota
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