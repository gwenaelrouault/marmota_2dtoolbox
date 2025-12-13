#include "update_state_event.h"

using namespace marmot::studio;

bool UpdateStateEvt::apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache)
{
    if (sprites.contains(_sprite_id) && (sprites[_sprite_id]->_states.contains(_id)))
    {
        sprites[_sprite_id]->_states[_id]->set(db_cache->_sprites[_sprite_id]->_states[_id]);
        return true;
    }
    return false;
}
