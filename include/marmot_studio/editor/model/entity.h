#pragma once

#include <vector>
#include <memory>
#include "entity_state.h"
#include  "sprite.hpp"

using namespace std;

namespace marmot::studio
{
    constexpr int SIZE_BUF = 256;

    struct Entity
    {
        Entity() : _name("NEW"), _request_focus(false), _editing(false), _index(0) {}
        virtual ~Entity() {}

        void add_state(unique_ptr<EntityState> &item);

        void create_new_state();

        void remove_state();

        std::string getName();

        vector<unique_ptr<EntityState>> &get_states();

        char _buffer[SIZE_BUF]{};

        uint64_t _id;

        vector<unique_ptr<EntityState>> _states;

        string _name;

        bool _request_focus;

        bool _editing;

        int _index;

        void set(const marmota::Sprite &other) {
            this->_id = other._id;
            this->_name = other._name;
        }
    };
}