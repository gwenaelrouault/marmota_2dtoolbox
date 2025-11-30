#pragma once

#include <string>
#include <vector>
#include "sprite.hpp"

namespace marmot::marmota
{
    struct Model {

        Model() {}
        virtual ~Model() {}

        std::vector<Sprite> _sprites;
    };
}