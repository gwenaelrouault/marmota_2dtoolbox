#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include "update_event.h"

using namespace std;

namespace marmot::studio
{
    class EventQueue
    {
    public:
        void push_event(unique_ptr<UpdateEvt>);
        unique_ptr<UpdateEvt> pop_event();
    private:
        queue<unique_ptr<UpdateEvt>> _queue;
        mutex _mutex;
    };
}