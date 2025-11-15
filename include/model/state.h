#pragma once

#include <string>

namespace marmot
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