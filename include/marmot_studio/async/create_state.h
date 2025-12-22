#pragma once

#include <filesystem>
#include <log4cpp/Category.hh>
#include <cstdint>
#include "task.hpp"
#include "asset_db.h"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_STATE_CREATE = 1;

    class CreateStateJob
    {
    public:
        explicit CreateStateJob(log4cpp::Category &logger,
                        shared_ptr<AssetDB> db,
                        MarmotaId id,
                    const string& name)
            : _logger(logger), _db(db), _id(id), _name(name) {}
        virtual ~CreateStateJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<AssetDB> _db;
        MarmotaId _id;
        string _name;
    };

    class CreateState : public Task<CreateStateJob>
    {
    public:
        explicit CreateState(log4cpp::Category &logger, CreateStateJob job) : Task(job), _logger(logger) {}
        virtual ~CreateState() {}

    private:
        log4cpp::Category &_logger;
    };
}