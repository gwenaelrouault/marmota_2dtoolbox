#include "create_entity.h"
#include "sdl_utils.h"
#include "db_error.h"

using namespace marmot::studio;

void CreateEntityCallback::onSuccess()
{
}

void CreateEntityCallback::onFailed(int err_code)
{
}

int CreateEntityJob::execute()
{
    try
    {
        _store->create_sprite(_name);
    }
    catch (marmota::DBException &e)
    {
        return ERROR_SPRITE_CREATION;
    }
    return RESULT_OK;
}
