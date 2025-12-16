#include "init_event.h"

using namespace marmot::studio;

bool InitEvt::apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache)
{
    for(auto& [id, sprite] : db_cache->_sprites) {
        sprites[id] = make_unique<EditorSprite>(id);
        sprites[id]->set(db_cache->_sprites[id]);
        for(auto& [state_id, state] : db_cache->_sprites[id]->_states) {
            sprites[id]->_states[state_id] = make_unique<EditorState>(state_id);
            sprites[id]->_states[state_id]->set(db_cache->_sprites[id]->_states[state_id]);
        }
    }
    return true;
}

void InitEvt::print(std::ostream& os) const
{
    os << "EVT:init()";
}