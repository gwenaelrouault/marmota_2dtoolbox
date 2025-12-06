#include "create_entity.h"
#include "sdl_utils.h"
#include "db_error.hpp"

using namespace marmot::studio;

void CreateEntityCallback::onSuccess()
{
    // load new created sprite ------------------------------------------------
    auto id = _model->get_current_sprite();
    if (id.has_value())
    {
        uint64_t sprite_id = id.value();
        _logger.infoStream() << "ASYNC:CreateSprite:load(" << sprite_id << ")";
        auto sprite = _store->load_sprite(sprite_id);
        _model->set_sprite(sprite);
    }
    _model->on_no_sprite();
}

void CreateEntityCallback::onFailed(int err_code)
{
    // notify sprite updated --------------------------------------------------
    _model->on_no_sprite();
}

int CreateEntityJob::execute()
{
    try
    {
        // create new sprite --------------------------------------------------
        _logger.infoStream() << "ASYNC:CreateSprite:create " << _name;
        uint64_t entity_id = _store->create_sprite(_name);
        _logger.infoStream() << "ASYNC:created sprite (" << _name << "," << entity_id << ")";
        // notify sprite update -----------------------------------------------
        _model->on_current_sprite(entity_id);
    }
    catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:CreateSprite:Error(" << e.what() << ")";
        return ERROR_SPRITE_CREATION;
    }
    return RESULT_OK;
}
