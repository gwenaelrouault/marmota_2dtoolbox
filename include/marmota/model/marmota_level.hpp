#pragma once
#include "marmota_types.hpp"
#include <vector>

namespace marmot::marmota
{
    struct MarmotaLevel {

        MarmotaLevel(const string& name, MarmotaId id) : _name(name), _id(id) {}
        ~MarmotaLevel() {}
        
        string _name;
        MarmotaId _id;
        vector<MarmotaId> _sprites;
    };
}