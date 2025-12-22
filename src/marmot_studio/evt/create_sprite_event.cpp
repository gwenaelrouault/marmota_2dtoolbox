#include "create_sprite_event.h"

using namespace marmot::studio;

bool CreateSpriteEvt::apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache)
{
    if (!sprites.contains(_id))
    {
        sprites[_id] = make_unique<EditorSprite>(_id);
        sprites[_id]->set(db_cache->_sprites[_id]);
        return true;
    }
    return false;
}

void CreateSpriteEvt::print(std::ostream &os) const
{
    os << "EVT:sprite:create(" << _id << ")";
}