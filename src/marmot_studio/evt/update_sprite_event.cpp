#include "update_sprite_event.h"

using namespace marmot::studio;

bool UpdateSpriteEvt::apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache)
{
    if (sprites.contains(_id))
    {
        sprites[_id]->set(db_cache->_sprites[_id]);
        return true;
    }
    return false;
}
