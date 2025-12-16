#include "open_project.h"
#include "db_error.hpp"

using namespace marmot::studio;

void OpenProjectJob::onSuccess()
{
    _logger.infoStream() << "ASYNC:OpenProject:open - OK";
    _model->load_level("default");
}

void OpenProjectJob::onFailed(int err_code) 
{
    _logger.infoStream() << "ASYNC:OpenProject:open - KO";
}

int OpenProjectJob::execute()
{
    _logger.infoStream() << "ASYNC:OpenProject:open(" << _path << ")";
    // open assets database ---------------------------------------------------
    try {
        _model->open_db(_path);
        return RESULT_OK;
    }
     catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:OpenProject:open(" << _path << ") - ERROR :" << e.what();
    }
    return ERROR_OPEN;
}

