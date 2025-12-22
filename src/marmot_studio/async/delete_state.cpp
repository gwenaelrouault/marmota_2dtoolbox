#include "delete_state.h"
#include "sdl_utils.h"
#include "db_error.hpp"

using namespace marmot::studio;

void DeleteStateJob::onSuccess()
{
    _logger.infoStream() << "ASYNC:DeleteState - OK";
}

void DeleteStateJob::onFailed(int err_code)
{
    _logger.infoStream() << "ASYNC:DeleteState - KO";
}

int DeleteStateJob::execute()
{
    _logger.infoStream() << "ASYNC:DeleteState(" << _id << ")";
    try
    {
        _db->delete_state(_sprite_id, _id);
        return RESULT_OK;
    }
    catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:DeleteState(" << _id << ") - ERROR :" << e.what();
    }
    return ERROR_STATE_DELETE;
}
