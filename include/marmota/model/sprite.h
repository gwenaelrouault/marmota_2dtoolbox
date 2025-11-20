#pragma once

#include <string>

namespace marmot::marmota
{
    class Sprite
    {
    public:
        Sprite(const std::string name) : _name(name) {}
        virtual ~Sprite() {}

    private:
        std::string _name;
    };
}