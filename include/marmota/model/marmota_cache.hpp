#pragma once

#include <string>
#include <map>
#include "marmota_sprite.hpp"
#include "marmota_level.hpp"

namespace marmot::marmota
{
    struct MarmotaCache {

        MarmotaCache() : _level(nullptr) {}
        virtual ~MarmotaCache() {}

        void clear();

        map<uint64_t,shared_ptr<MarmotaSprite>> _sprites;

        shared_ptr<MarmotaLevel> _level;
    };
}