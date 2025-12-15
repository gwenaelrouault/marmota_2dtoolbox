#include "create_state.h"
#include "sdl_utils.h"
#include "db_error.hpp"

using namespace marmot::studio;

void CreateStateJob::onSuccess()
{
    _logger.infoStream() << "ASYNC:CreateState:create new state [OK]";
}

void CreateStateJob::onFailed(int err_code)
{
    _logger.infoStream() << "ASYNC:CreateState:create new state [KO]";
}

int CreateStateJob::execute()
{
    try
    {
        _logger.infoStream() << "ASYNC:CreateState:create new state";
        _model->create_new_state(_id, _name);
        _logger.infoStream() << "ASYNC:CreateState:created new state";
    }
    catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:CreateState:Error(" << e.what() << ")";
        return ERROR_STATE_CREATE;
    }
    return RESULT_OK;
}
