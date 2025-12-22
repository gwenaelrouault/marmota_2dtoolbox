#pragma once

#include <log4cpp/Category.hh>
#include <filesystem>
#include "task.hpp"
#include "asset_db.h"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_OPEN = 1;

    class OpenProjectJob
    {
    public:
        explicit OpenProjectJob(log4cpp::Category &logger,
                       shared_ptr<AssetDB> db,
                       filesystem::path &project)
            : _logger(logger), _db(db), _path(project) {}
        virtual ~OpenProjectJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<AssetDB> _db;
        filesystem::path _path;
    };

    class OpenProject : public Task<OpenProjectJob>
    {
    public:
        explicit OpenProject(log4cpp::Category &logger, OpenProjectJob job) : Task(job), _logger(logger) {}
        virtual ~OpenProject() {}

    private:
        log4cpp::Category &_logger;
    };
}