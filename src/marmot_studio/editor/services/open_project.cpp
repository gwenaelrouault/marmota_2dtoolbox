#include "open_project.h"
#include "db_error.hpp"

using namespace marmot::studio;

void OpenProjectCallback::onSuccess()
{
    _logger.infoStream() << "ASYNC:OpenProject:open - OK";
}

void OpenProjectCallback::onFailed(int err_code) 
{
    _logger.infoStream() << "ASYNC:OpenProject:open - KO";
}

int OpenProjectJob::execute()
{
    _logger.infoStream() << "ASYNC:OpenProject:open(" << _path << ")";
    // open assets database ---------------------------------------------------
    try {
        _store->open(_path);
        return RESULT_OK;
    }
     catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:OpenProject:open(" << _path << ") - ERROR :" << e.what();
    }
    return ERROR_OPEN;
}

