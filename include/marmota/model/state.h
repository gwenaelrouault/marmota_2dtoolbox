#pragma once

#include <string>

namespace marmot::marmota
{
    class State
    {
    public:
        State(const std::string name) : _name(name) {}
        virtual ~State() {}

    private:
        std::string _name;
    };
}