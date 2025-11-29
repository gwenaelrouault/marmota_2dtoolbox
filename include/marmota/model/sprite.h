#pragma once

#include <string>
#include <memory>
#include <vector>
#include "state.h"

using namespace std;

namespace marmot::marmota
{
    class Sprite
    {
    public:
        Sprite(const std::string name) : _name(name) {}
        virtual ~Sprite() {}

    private:
        std::string _name;
        vector<shared_ptr<State>> _states;
    };
}