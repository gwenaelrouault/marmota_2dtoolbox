#pragma once

#include <memory>
#include <map>
#include "marmota_state.hpp"

using namespace std;

namespace marmot::marmota
{
    struct MarmotaSprite
    {
        MarmotaSprite() {}
        MarmotaSprite(const string& name) : _name(name), _id(-1) {}
        MarmotaSprite(const string& name, MarmotaId id) : _name(name), _id(id) {}
        virtual ~MarmotaSprite() {}

        std::string _name;
        MarmotaId _id;
        map<MarmotaId, shared_ptr<MarmotaState>> _states;

        void update(shared_ptr<MarmotaSprite>&other);
    };
}