#include "marmota_sprite.hpp"

using namespace marmot::marmota;

void MarmotaSprite::update(shared_ptr<MarmotaSprite>&other) {
    _name = other->_name;
    _states.clear();
    for(auto state : other->_states) {
        _states[state.first] = std::move(state.second);
    }
}