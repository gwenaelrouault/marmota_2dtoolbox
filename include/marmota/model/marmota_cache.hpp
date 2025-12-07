#pragma once

#include <string>
#include <map>
#include "marmota_sprite.hpp"

namespace marmot::marmota
{
    struct MarmotaCache {

        MarmotaCache() {}
        virtual ~MarmotaCache() {}

        void clear();

        map<uint64_t,shared_ptr<MarmotaSprite>> _sprites;
    };
}