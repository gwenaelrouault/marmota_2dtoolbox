#include "create_entity.h"
#include "sdl_utils.h"
#include "db_error.hpp"

using namespace marmot::studio;

void CreateEntityJob::onSuccess()
{
    // load new created sprite ------------------------------------------------
    auto id = _model->get_current_sprite();
    if (id.has_value())
    {
        uint64_t sprite_id = id.value();
        _logger.infoStream() << "ASYNC:CreateSprite:load(" << sprite_id << ")";
        //_store->load_sprite(sprite_id);
    }
    // notify sprite updated --------------------------------------------------
    _model->on_no_sprite();
}

void CreateEntityJob::onFailed(int err_code)
{
    // notify sprite updated --------------------------------------------------
    _model->on_no_sprite();
}

int CreateEntityJob::execute()
{
    try
    {
        _logger.infoStream() << "ASYNC:CreateSprite:create new sprite";
        _model->create_new_sprite();
        _logger.infoStream() << "ASYNC:created new sprite";
    }
    catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:CreateSprite:Error(" << e.what() << ")";
        return ERROR_SPRITE_CREATION;
    }
    return RESULT_OK;
}
