#pragma once

#include <vector>
#include <memory>
#include "entity_state.h"

using namespace std;

namespace marmot::studio
{
    constexpr int SIZE_BUF = 256;    
    
    class Entity
    {
    public:
        Entity() : _name("NEW"), _request_focus(false), _editing(false), _index(0) {}
        virtual ~Entity() {
        }

        void add_state(unique_ptr<EntityState>& item);

        void create_new_state();

        void remove_state();

        bool is_editing();

        bool is_requested_focus();

        void set_editing(bool flag);

        void set_request_focus(bool flag);

        void set_name(const std::string& name);

        std::string getName();

        vector<unique_ptr<EntityState>>& get_states();
        
        char _buffer[SIZE_BUF]{};
    private:
        vector<unique_ptr<EntityState>> _states;

        string _name;
        bool _request_focus;
        bool _editing;
        int _index;
        
    };
}