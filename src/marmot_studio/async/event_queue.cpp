#include "event_queue.h"

using namespace marmot::studio;

void EventQueue::push_event(unique_ptr<UpdateEvt> evt)
{
    lock_guard<mutex> lock(_mutex);
    {
        _queue.push(std::move(evt));
    }
}

unique_ptr<UpdateEvt> EventQueue::pop_event()
{
    lock_guard<mutex> lock(_mutex);
    {
        if (!_queue.empty())
        {
            auto evt = std::move(_queue.back());
            _queue.pop();
            return evt;
        }
    }
    return nullptr;
}