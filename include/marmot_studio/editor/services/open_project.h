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

    constexpr int ERROR_OPEN = 1;

    class OpenProjectCallback
    {
    public:
        OpenProjectCallback(log4cpp::Category &logger) : _logger(logger) {}
        virtual ~OpenProjectCallback() {}

        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
    };

    class OpenProjectJob
    {
    public:
        OpenProjectJob(log4cpp::Category &logger, 
            shared_ptr<SpritesModel>& model, 
            shared_ptr<marmota::MarmotaAssetStore>& store, 
            filesystem::path& project) 
            : _logger(logger), _model(model), _store(store), _path(project) {}
        virtual ~OpenProjectJob() {}
        int execute();

    private:
        log4cpp::Category &_logger;
        shared_ptr<SpritesModel>& _model;
        shared_ptr<marmota::MarmotaAssetStore>& _store;
        filesystem::path _path;
    };

    class OpenProject : public Task<OpenProjectJob, OpenProjectCallback>
    {
    public:
        OpenProject(log4cpp::Category &logger, OpenProjectJob job, OpenProjectCallback cb) : Task(job, cb), _logger(logger) {}
        virtual ~OpenProject() {}

    private:
        log4cpp::Category &_logger;
        
    };
}