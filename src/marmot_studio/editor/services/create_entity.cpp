#include "create_entity.h"
#include "sdl_utils.h"
#include "db_error.h"

using namespace marmot::studio;

void CreateEntityCallback::onSuccess()
{
    auto id = _model->get_current_sprite();
    if (id.has_value()) {
        struct marmota::Sprite sprite;
        _store->load_entity(id.value(), sprite);
        _model->set_sprite(sprite);
    }
    _model->on_no_sprite();
}

void CreateEntityCallback::onFailed(int err_code)
{
    _model->on_no_sprite();
}

int CreateEntityJob::execute()
{
    try
    {
        uint64_t entity_id =  _store->create_sprite(_name);
        _model->on_current_sprite(entity_id);
    }
    catch (marmota::DBException &e)
    {
        return ERROR_SPRITE_CREATION;
    }
    return RESULT_OK;
}
