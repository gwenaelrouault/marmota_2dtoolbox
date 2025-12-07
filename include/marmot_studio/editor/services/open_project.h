#pragma once

#include <log4cpp/Category.hh>
#include <filesystem>
#include "task.hpp"
#include "sprites_model.h"
#include "marmota_asset_store.hpp"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_OPEN = 1;

    class OpenProjectJob
    {
    public:
        OpenProjectJob(log4cpp::Category &logger,
                       shared_ptr<SpritesModel> &model,
                       filesystem::path &project)
            : _logger(logger), _model(model), _path(project) {}
        virtual ~OpenProjectJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<SpritesModel> &_model;
        filesystem::path _path;
    };

    class OpenProject : public Task<OpenProjectJob>
    {
    public:
        OpenProject(log4cpp::Category &logger, OpenProjectJob job) : Task(job), _logger(logger) {}
        virtual ~OpenProject() {}

    private:
        log4cpp::Category &_logger;
    };
}