#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "task.hpp"

using namespace std;

namespace marmot
{
    class Worker
    {
    public:
        Worker() : _running(true), _worker(&Worker::threadLoop, this) {}

        void async(std::unique_ptr<ITask> task);

        void stop();
    private:
        void threadLoop();

        std::atomic<bool> _running;
        std::queue<std::unique_ptr<ITask>> _tasks;
        std::thread _worker;
        std::condition_variable _cv;
        std::mutex _mutex;
    };
}