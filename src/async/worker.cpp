#include "worker.hpp"

using namespace marmot;

void Worker::async(std::unique_ptr<ITask> task)
{
    {
        std::scoped_lock lock(_mutex);
        _tasks.push(std::move(task));
    }
    _cv.notify_one();
}

void Worker::stop()
{
    if (_running.exchange(false))
    {
        _cv.notify_one();
        if (_worker.joinable())
            _worker.join();
    }
}

void Worker::threadLoop()
{
    while (_running)
    {
        std::unique_ptr<ITask> task;
        {
            std::unique_lock lock(_mutex);
            _cv.wait(lock, [&]
                     { return !_tasks.empty() || !_running; });
            if (!_running && _tasks.empty())
                break;
            task = std::move(_tasks.front());
            _tasks.pop();
        }
        task->run();
    }
}