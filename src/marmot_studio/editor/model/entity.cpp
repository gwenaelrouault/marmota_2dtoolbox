#include "entity.h"

using namespace marmot::studio;

void Entity::add_state(unique_ptr<EntityState> &item)
{
    _states.push_back(std::move(item));
}

void Entity::create_new_state()
{
    auto new_state = make_unique<EntityState>(to_string(_index++));
    
    add_state(new_state);
}

void Entity::remove_state()
{
    _states.pop_back();
}

vector<unique_ptr<EntityState>>& Entity::get_states() {
    return _states;
}