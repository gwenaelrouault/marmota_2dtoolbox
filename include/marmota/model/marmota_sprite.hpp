#pragma once

#include <string>
#include <memory>
#include <map>
#include "marmota_state.hpp"
#include <cstdint>

using namespace std;

namespace marmot::marmota
{
    struct MarmotaSprite
    {
        MarmotaSprite() {}
        MarmotaSprite(const string& name) : _name(name), _id(-1) {}
        MarmotaSprite(const string& name, uint64_t id) : _name(name), _id(id) {}
        virtual ~MarmotaSprite() {}

        std::string _name;
        uint64_t _id;
        map<uint64_t, shared_ptr<MarmotaState>> _states;

        void update(shared_ptr<MarmotaSprite>&other);
    };
}