#include "update_sprite.h"
#include "sdl_utils.h"
#include "db_error.hpp"

using namespace marmot::studio;

void UpdateSpriteJob::onSuccess()
{
    _logger.infoStream() << "ASYNC:UpdateSprite:status[OK]";
}

void UpdateSpriteJob::onFailed(int err_code)
{
    _logger.infoStream() << "ASYNC:UpdateSprite:status[KO]";
}

int UpdateSpriteJob::execute()
{
    try
    {
        _logger.infoStream() << "ASYNC:UpdateSprite";
        _model->update_sprite(_id, _name);
    }
    catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:UpdateSprite:Error(" << e.what() << ")";
        return ERROR_SPRITE_UPDATE;
    }
    return RESULT_OK;
}
