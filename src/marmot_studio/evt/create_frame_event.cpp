#include "create_frame_event.h"
#include "editor_frame.h"

using namespace marmot::studio;

bool CreateFrameEvt::apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache)
{
    if (sprites.contains(_sprite_id) && (sprites[_sprite_id]->_states.contains(_id)) && (!sprites[_sprite_id]->_states[_state_id]->_frames.contains(_id)))
    {
        sprites[_sprite_id]->_states[_state_id]->_frames[_id] = make_unique<EditorFrame>(_state_id, _id, _num);
        sprites[_sprite_id]->_states[_state_id]->_frames[_id]->set(db_cache->_sprites[_sprite_id]->_states[_state_id]->_frames[_id]);
        return true;
    }
    return false;
}

void CreateFrameEvt::print(std::ostream &os) const
{
    os << "EVT:frame:create(" << _id << ",state_id=" << ")";
}