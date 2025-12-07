#pragma once

#include <filesystem>
#include <log4cpp/Category.hh>
#include "task.hpp"
#include "sprites_model.h"
#include "marmota_asset_store.hpp"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_SPRITE_CREATION = 1;

    class CreateSpriteJob
    {
    public:
        CreateSpriteJob(log4cpp::Category &logger,
                        shared_ptr<SpritesModel> &model)
            : _logger(logger), _model(model) {}
        virtual ~CreateSpriteJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<SpritesModel> &_model;
    };

    class CreateSprite : public Task<CreateSpriteJob>
    {
    public:
        CreateSprite(log4cpp::Category &logger, CreateSpriteJob job) : Task(job), _logger(logger) {}
        virtual ~CreateSprite() {}

    private:
        log4cpp::Category &_logger;
    };
}