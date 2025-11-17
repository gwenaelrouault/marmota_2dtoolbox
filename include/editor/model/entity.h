#pragma once

#include <vector>
#include <memory>
#include "entity_state.h"

using namespace std;

namespace marmot::studio
{
    class Entity
    {
    public:
        Entity() {}
        virtual ~Entity() {}

        void add_state(unique_ptr<EntityState>& item);

        void create_new_state();

        void remove_state();

    private:
        vector<unique_ptr<EntityState>> _states;
    };
}