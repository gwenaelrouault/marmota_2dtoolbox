#pragma once
#include <log4cpp/Category.hh>
#include "task.hpp"
#include "import_sheet_model.h"

using namespace std;

namespace marmot::studio
{
    class ImportSheetJob
    {
    public:
        ImportSheetJob(log4cpp::Category &logger, std::shared_ptr<ImportSheetModel> &model, const string &filename, int width, int height)
            : _logger(logger), _model(model), _path(filename), _width(width), _height(height) {}
        virtual ~ImportSheetJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        std::shared_ptr<ImportSheetModel> &_model;
        filesystem::path _path;
        int _width;
        int _height;
    };

    class ImportSheet : public Task<ImportSheetJob>
    {
    public:
        ImportSheet(log4cpp::Category &logger, ImportSheetJob job) : Task(job), _logger(logger) {}
        virtual ~ImportSheet() {}

    private:
        log4cpp::Category &_logger;
    };
}