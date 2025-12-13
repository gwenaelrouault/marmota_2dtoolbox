#pragma once

#include <filesystem>
#include <log4cpp/Category.hh>
#include <cstdint>
#include "task.hpp"
#include "sprites_model.h"
#include "marmota_asset_store.hpp"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_SPRITE_UPDATE = 1;

    class UpdateSpriteJob
    {
    public:
        UpdateSpriteJob(log4cpp::Category &logger,
                        shared_ptr<SpritesModel> model,
                        uint64_t id,
                    const string& name)
            : _logger(logger), _model(model), _id(id), _name(name) {}
        virtual ~UpdateSpriteJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<SpritesModel> _model;
        uint64_t _id;
        string _name;
    };

    class UpdateSprite : public Task<UpdateSpriteJob>
    {
    public:
        UpdateSprite(log4cpp::Category &logger, UpdateSpriteJob job) : Task(job), _logger(logger) {}
        virtual ~UpdateSprite() {}

    private:
        log4cpp::Category &_logger;
    };
}