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

    class CreateEntityJob
    {
    public:
        CreateEntityJob(log4cpp::Category &logger,
                        shared_ptr<SpritesModel> &model)
            : _logger(logger), _model(model) {}
        virtual ~CreateEntityJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<SpritesModel> &_model;
    };

    class CreateEntity : public Task<CreateEntityJob>
    {
    public:
        CreateEntity(log4cpp::Category &logger, CreateEntityJob job) : Task(job), _logger(logger) {}
        virtual ~CreateEntity() {}

    private:
        log4cpp::Category &_logger;
    };
}