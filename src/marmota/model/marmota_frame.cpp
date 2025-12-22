#include "marmota_frame.hpp"

using namespace marmot::marmota;

void MarmotaFrame::update(shared_ptr<MarmotaFrame>&other) {
    _state_id = other->_state_id;
    _num = other->_num;
}
