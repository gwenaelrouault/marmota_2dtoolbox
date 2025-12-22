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

    constexpr int ERROR_SPRITE_UPDATE = 1;

    class UpdateSpriteJob
    {
    public:
        explicit UpdateSpriteJob(log4cpp::Category &logger,
                        shared_ptr<AssetDB> db,
                        MarmotaId id,
                    const string& name)
            : _logger(logger), _db(db), _id(id), _name(name) {}
        virtual ~UpdateSpriteJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<AssetDB> _db;
        MarmotaId _id;
        string _name;
    };

    class UpdateSprite : public Task<UpdateSpriteJob>
    {
    public:
        explicit UpdateSprite(log4cpp::Category &logger, UpdateSpriteJob job) : Task(job), _logger(logger) {}
        virtual ~UpdateSprite() {}

    private:
        log4cpp::Category &_logger;
    };
}