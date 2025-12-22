#pragma once

#include <filesystem>
#include <log4cpp/Category.hh>
#include "task.hpp"
#include "asset_db.h"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_STATE_DELETE = 1;

    class DeleteStateJob
    {
    public:
        explicit DeleteStateJob(log4cpp::Category &logger,
                        shared_ptr<AssetDB> db,
                        MarmotaId sprite_id,
                        MarmotaId id)
            : _logger(logger), _db(db), _id(id), _sprite_id(sprite_id) {}
        virtual ~DeleteStateJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<AssetDB> _db;
        MarmotaId _id;
        MarmotaId _sprite_id;
    };

    class DeleteState : public Task<DeleteStateJob>
    {
    public:
        explicit DeleteState(log4cpp::Category &logger, DeleteStateJob job) : Task(job), _logger(logger) {}
        virtual ~DeleteState() {}

    private:
        log4cpp::Category &_logger;
    };
}