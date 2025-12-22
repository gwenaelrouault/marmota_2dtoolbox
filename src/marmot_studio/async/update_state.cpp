#include "update_state.h"
#include "sdl_utils.h"
#include "db_error.hpp"

using namespace marmot::studio;

void UpdateStateJob::onSuccess()
{
    _logger.infoStream() << "ASYNC:UpdateState - OK";
}

void UpdateStateJob::onFailed(int err_code) 
{
    _logger.infoStream() << "ASYNC:UpdateState - KO";
}

int UpdateStateJob::execute()
{
    _logger.infoStream() << "ASYNC:UpdateState(" << _id << ")";
    try {
        return RESULT_OK;
    }
     catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:UpdateState(" << _id << ") - ERROR :" << e.what();
    }
    return ERROR_STATE_UPDATE;
}