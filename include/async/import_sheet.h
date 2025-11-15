#pragma once
#include <log4cpp/Category.hh>
#include "task.h"
#include "import_sheet_model.h"

using namespace std;

namespace marmot
{

    class ImportSheetCallback
    {
    public:
        ImportSheetCallback(log4cpp::Category &logger) : _logger(logger) {}
        virtual ~ImportSheetCallback() {}

        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
    };

    class ImportSheetJob
    {
    public:
        ImportSheetJob(log4cpp::Category &logger, std::shared_ptr<ImportSheetModel>& model, const string& filename, int width, int height) 
            : _logger(logger), _model(model), _path(filename), _width(width), _height(height) {}
        virtual ~ImportSheetJob() {}
        int execute();

    private:
        log4cpp::Category &_logger;
        std::shared_ptr<ImportSheetModel>& _model;
        filesystem::path _path;
        int _width;
        int _height;
    };

    class ImportSheet : public Task<ImportSheetJob, ImportSheetCallback>
    {
    public:
        ImportSheet(log4cpp::Category &logger, ImportSheetJob job, ImportSheetCallback cb) : Task(job, cb), _logger(logger) {}
        virtual ~ImportSheet() {}

    private:
        log4cpp::Category &_logger;
        
    };
}