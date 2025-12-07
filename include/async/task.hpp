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
    concept Job = requires(T job, int err_code) {
        { job.execute() } -> std::same_as<int>;
        { job.onSuccess() } -> same_as<void>;
        { job.onFailed(err_code) } -> same_as<void>;
    };

    template <typename Job>
    class Task : public ITask
    {
    public:
        Task(Job job) : _job(std::move(job)) {}
        virtual ~Task() {}

        void run()
        {
            auto result = _job.execute();
            if (result == 0)
            {
                _job.onSuccess();
            }
            else
            {
                _job.onFailed(result);
            }
        }

    private:
        Job _job;
    };
}