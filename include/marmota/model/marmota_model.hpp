#pragma once

#include <string>
#include <map>
#include "marmota_sprite.hpp"

namespace marmot::marmota
{
    struct MarmotaModel {

        MarmotaModel() {}
        virtual ~MarmotaModel() {}

        map<uint64_t,shared_ptr<MarmotaSprite>> _sprites;
    };
}