#pragma once

#include "marmota_types.hpp"
#include "marmota_frame.hpp"
#include "sdl_utils.h"

namespace marmot::studio
{
    struct EditorFrame {

        explicit EditorFrame(MarmotaId state_id, MarmotaId id, int num_frame)
            : _id(id), _state_id(state_id), _num_frame(num_frame), _texture(nullptr) {}
        virtual ~EditorFrame() {}

        MarmotaId _id;
        MarmotaId _state_id;
        int _num_frame;

        TexturePtr _texture;

        // get from store =====================================================
        void set(shared_ptr<marmota::MarmotaFrame> &other)
        {
            this->_id = other->_id;
            this->_state_id = other->_state_id;
            this->_num_frame = other->_num;
        }
    };
}