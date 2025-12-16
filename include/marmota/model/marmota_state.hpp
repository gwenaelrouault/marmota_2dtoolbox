#pragma once

#include <map>
#include <memory>
#include "marmota_frame.hpp"

namespace marmot::marmota
{
    struct MarmotaState
    {
        MarmotaState() {}
        MarmotaState(const string &name, int width, int height) 
            : _name(name), _loop(false), _width(width), _height(height), _speed(0) {}
        MarmotaState(const string &name, MarmotaId id, bool loop, int speed, int width, int height) 
            : _name(name), _id(id), _loop(loop), _speed(speed), _width(width), _height(height) {}
        virtual ~MarmotaState() {}

        void update(shared_ptr<MarmotaState>&other);

        MarmotaId _id;
        string _name;
        bool _loop;
        int _width;
        int _height;
        int _speed;
        map<MarmotaId, shared_ptr<MarmotaFrame>> _frames;
    };
}
