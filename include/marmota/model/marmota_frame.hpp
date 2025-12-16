#pragma once
#include "marmota_types.hpp"

namespace marmot::marmota
{
    struct MarmotaFrame
    {
        MarmotaFrame() : _id(-1) {}
        MarmotaFrame(MarmotaId id) : _id(id) {}
        virtual ~MarmotaFrame() {}
        
        MarmotaId _id;
    };
}