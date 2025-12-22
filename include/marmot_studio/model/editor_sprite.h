#pragma once

#include <vector>
#include <map>
#include <memory>
#include "editor_state.h"
#include "marmota_sprite.hpp"

using namespace std;

namespace marmot::studio
{
    constexpr int SIZE_BUF = 32;

    struct EditorSprite
    {
        EditorSprite(uint64_t id) : _id(id), _name("NEW"), _request_focus(false), _editing(false), _index(0) {}
        virtual ~EditorSprite() {}

        void add_state(unique_ptr<EditorState> &item);

        void remove_state();

        map<MarmotaId, unique_ptr<EditorState>> _states;

        char _buffer[SIZE_BUF]{};

        MarmotaId _id;

        string _name;

        bool _request_focus;

        bool _editing;

        int _index;

        // get from store =====================================================
        void set(shared_ptr<marmota::MarmotaSprite> &other)
        {
            this->_id = other->_id;
            this->_name = other->_name;
        }
    };
}