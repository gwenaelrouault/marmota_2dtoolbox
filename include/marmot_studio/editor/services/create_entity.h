#pragma once

#include <log4cpp/Category.hh>
#include "task.h"
#include "sprites_model.h"
#include <filesystem>
#include "marmota_asset_store.h"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_SPRITE_CREATION = 1;

    class CreateEntityCallback
    {
    public:
        CreateEntityCallback(log4cpp::Category &logger) : _logger(logger) {}
        virtual ~CreateEntityCallback() {}

        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
    };

    class CreateEntityJob
    {
    public:
        CreateEntityJob(log4cpp::Category &logger, 
            shared_ptr<SpritesModel>& model, 
            shared_ptr<marmota::MarmotaAssetStore>& store, 
            const string& name) 
            : _logger(logger), _model(model), _store(store), _name(name) {}
        virtual ~CreateEntityJob() {}
        int execute();

    private:
        log4cpp::Category &_logger;
        shared_ptr<SpritesModel>& _model;
        shared_ptr<marmota::MarmotaAssetStore>& _store;
        string _name;
    };

    class CreateEntity : public Task<CreateEntityJob, CreateEntityCallback>
    {
    public:
        CreateEntity(log4cpp::Category &logger, CreateEntityJob job, CreateEntityCallback cb) : Task(job, cb), _logger(logger) {}
        virtual ~CreateEntity() {}

    private:
        log4cpp::Category &_logger;
        
    };
}