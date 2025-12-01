#pragma once

#include <string>
#include <vector>
#include "marmota_sprite.hpp"

namespace marmot::marmota
{
    struct MarmotaModel {

        MarmotaModel() {}
        virtual ~MarmotaModel() {}

        vector<shared_ptr<MarmotaSprite>> _sprites;
    };
}