#pragma once
#include "marmota_types.hpp"

namespace marmot::marmota
{
    struct MarmotaFrame
    {
        MarmotaFrame(MarmotaId id, MarmotaId state_id, int num) : _id(id), _state_id(state_id), _num(num) {}
        virtual ~MarmotaFrame() {}

        void update(shared_ptr<MarmotaFrame>&other);
        
        MarmotaId _id;
        MarmotaId _state_id;
        int _num;
    };
}