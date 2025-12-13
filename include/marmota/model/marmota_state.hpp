#pragma once

#include <string>
#include <map>
#include <memory>
#include "marmota_frame.hpp"

namespace marmot::marmota
{
    struct MarmotaState
    {
        MarmotaState() {}
        MarmotaState(const std::string name, int width, int height) 
            : _name(name), _loop(false), _width(width), _height(height), _speed(0) {}
        MarmotaState(const std::string name, uint64_t id, bool loop, int speed, int width, int height) 
            : _name(name), _id(id), _loop(loop), _speed(speed), _width(width), _height(height) {}
        virtual ~MarmotaState() {}

        void update(shared_ptr<MarmotaState>&other);

        uint64_t _id;
        string _name;
        bool _loop;
        int _width;
        int _height;
        int _speed;
        map<uint64_t, shared_ptr<MarmotaFrame>> _frames;
    };
}
