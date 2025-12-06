#pragma once

#include <string>
#include <map>
#include "marmota_frame.hpp"

namespace marmot::marmota
{
    struct MarmotaState
    {
        MarmotaState(const std::string name, int width, int height) : _name(name), _loop(false), _width(width), _height(height) {}
        MarmotaState(const std::string name, uint64_t id, bool loop, int width, int height) 
        : _name(name), _id(id), _loop(loop), _width(width), _height(height) {}
        virtual ~MarmotaState() {}

        uint64_t _id;
        string _name;
        bool _loop;
        int _width;
        int _height;
        map<uint64_t, shared_ptr<MarmotaFrame>> _frames;
    };
}