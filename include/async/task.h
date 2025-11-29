#pragma once

#include <memory>
#include <queue>

using namespace std;

namespace marmot
{

    constexpr int RESULT_OK = 0;

    struct ITask
    {
    public:
        virtual ~ITask() = default;
        virtual void run() = 0;
    };

    template <typename T>
    concept Job = requires(T job) {
        { job.execute() } -> std::same_as<int>;
    };

    template <typename T>
    concept Callback = requires(T cb, int err_code) {
        { cb.onSuccess() } -> same_as<void>;
        { cb.onFailed(err_code) } -> same_as<void>;
    };

    template <typename Job, typename Callback>
    class Task : public ITask
    {
    public:
        Task(Job job, Callback cb) : _job(std::move(job)), _callback(std::move(cb)) {}
        virtual ~Task() {}

        void run()
        {
            auto result = _job.execute();
            if (result == 0)
            {
                _callback.onSuccess();
            }
            else
            {
                _callback.onFailed(result);
            }
        }

    private:
        Callback _callback;
        Job _job;
    };
}