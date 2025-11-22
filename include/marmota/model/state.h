#pragma once

#include <string>

namespace marmot::marmota
{
    class State
    {
    public:
        State(const std::string name, int width, int height) : _name(name), _loop(false), _width(width), _height(height) {}
        virtual ~State() {}

    private:
        std::string _name;
        bool _loop;
        int _width;
        int _height;
    };
}