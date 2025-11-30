#pragma once

#include <string>

namespace marmot::marmota
{
    struct State
    {
        State(const std::string name, int width, int height) : _name(name), _loop(false), _width(width), _height(height) {}
        virtual ~State() {}

        std::string _name;
        bool _loop;
        int _width;
        int _height;
    };
}