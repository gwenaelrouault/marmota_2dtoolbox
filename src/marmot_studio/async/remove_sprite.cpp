#include "remove_sprite.h"
#include "sdl_utils.h"
#include "db_error.hpp"

using namespace marmot::studio;

void RemoveSpriteJob::onSuccess()
{
    _logger.infoStream() << "ASYNC:RemoveSprite:create new sprite [OK]";
}

void RemoveSpriteJob::onFailed(int err_code)
{
    _logger.infoStream() << "ASYNC:RemoveSprite:create new sprite [KO]";
}

int RemoveSpriteJob::execute()
{
    try
    {
        _logger.infoStream() << "ASYNC:RemoveSprite:remove sprite " << _id;
        _model->remove_sprite(_id);
        _logger.infoStream() << "ASYNC:removed sprite " << _id;
    }
    catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:RemoveSprite:Error(" << e.what() << ")";
        return ERROR_SPRITE_REMOVE;
    }
    return RESULT_OK;
}
