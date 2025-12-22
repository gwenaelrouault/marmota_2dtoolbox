#include "create_state_event.h"

using namespace marmot::studio;

bool CreateStateEvt::apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache)
{
    if (sprites.contains(_sprite_id) && (!sprites[_sprite_id]->_states.contains(_id)))
    {
        sprites[_sprite_id]->_states[_id] = make_unique<EditorState>(_id);
        sprites[_sprite_id]->_states[_id]->set(db_cache->_sprites[_sprite_id]->_states[_id]);
        return true;
    }
    return false;
}

void CreateStateEvt::print(std::ostream &os) const
{
    os << "EVT:state:create(" << _id << "," << _sprite_id << ")";
}