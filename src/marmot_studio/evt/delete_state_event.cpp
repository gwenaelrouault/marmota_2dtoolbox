#include "delete_state_event.h"

using namespace marmot::studio;

bool DeleteStateEvt::apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache)
{
    if (sprites.contains(_sprite_id) && (sprites[_sprite_id]->_states.contains(_id)))
    {
        sprites[_sprite_id]->_states.erase(_id);
        return true;
    }
    return false;
}

void DeleteStateEvt::print(std::ostream &os) const
{
    os << "EVT:state:delete(" << _id << "," << _sprite_id << ")";
}