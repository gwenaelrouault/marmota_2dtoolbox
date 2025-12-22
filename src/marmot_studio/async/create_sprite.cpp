#include "create_sprite.h"
#include "sdl_utils.h"
#include "db_error.hpp"

using namespace marmot::studio;

void CreateSpriteJob::onSuccess()
{
    _logger.infoStream() << "ASYNC:CreateSprite:create new sprite [OK]";
}

void CreateSpriteJob::onFailed(int err_code)
{
    _logger.infoStream() << "ASYNC:CreateSprite:create new sprite [KO]";
}

int CreateSpriteJob::execute()
{
    try
    {
        _logger.infoStream() << "ASYNC:CreateSprite:create new sprite";
        _db->create_new_sprite();
        _logger.infoStream() << "ASYNC:created new sprite";
    }
    catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:CreateSprite:Error(" << e.what() << ")";
        return ERROR_SPRITE_CREATION;
    }
    return RESULT_OK;
}
