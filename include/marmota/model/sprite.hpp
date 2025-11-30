#pragma once

#include <string>
#include <memory>
#include <vector>
#include "state.hpp"
#include <cstdint>

using namespace std;

namespace marmot::marmota
{
    struct Sprite
    {
        Sprite() {}
        Sprite(const std::string name) : _name(name), _id(-1) {}
        virtual ~Sprite() {}

        std::string _name;
        uint64_t _id;
        vector<shared_ptr<State>> _states;
    };
}