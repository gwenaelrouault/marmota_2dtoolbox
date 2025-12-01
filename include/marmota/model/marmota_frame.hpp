#pragma once
#include <cstdint>

using namespace std;

namespace marmot::marmota
{
    struct MarmotaFrame
    {
        MarmotaFrame() : _id(-1) {}
        MarmotaFrame(uint64_t id) : _id(id) {}
        virtual ~MarmotaFrame() {}
        
        uint64_t _id;
    };
}