#include "delete_sprite_event.h"

using namespace marmot::studio;

bool DeleteSpriteEvt::apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache)
{
    if (sprites.contains(_id))
    {
        sprites.erase(_id);
        return true;
    }
    return false;
}

void DeleteSpriteEvt::print(std::ostream& os) const
{
    os << "EVT:sprite:delete(" << _id <<  ")";
}