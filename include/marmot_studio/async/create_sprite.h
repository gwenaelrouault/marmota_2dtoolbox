#pragma once

#include <filesystem>
#include <log4cpp/Category.hh>
#include "task.hpp"
#include "asset_db.h"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_SPRITE_CREATION = 1;

    class CreateSpriteJob
    {
    public:
        explicit CreateSpriteJob(log4cpp::Category &logger,
                        shared_ptr<AssetDB> db)
            : _logger(logger), _db(db) {}
        virtual ~CreateSpriteJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<AssetDB> _db;
    };

    class CreateSprite : public Task<CreateSpriteJob>
    {
    public:
        explicit CreateSprite(log4cpp::Category &logger, CreateSpriteJob job) : Task(job), _logger(logger) {}
        virtual ~CreateSprite() {}

    private:
        log4cpp::Category &_logger;
    };
}