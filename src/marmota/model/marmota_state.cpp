#include "marmota_state.hpp"

using namespace marmot::marmota;

void MarmotaState::update(shared_ptr<MarmotaState>&other) {
    _name = other->_name;
    _frames.clear();
    for(auto frame : other->_frames) {
        _frames[frame.first] = std::move(frame.second);
    }
}
