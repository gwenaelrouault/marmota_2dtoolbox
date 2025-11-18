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

bool Entity::is_editing()
{
    return _editing;
}

bool Entity::is_requested_focus()
{
    return _request_focus;
}

void Entity::set_editing(bool flag)
{
    _editing = flag;
}

void Entity::set_request_focus(bool flag)
{
    _request_focus = flag;
}

void Entity::set_name(const std::string &name)
{
    _name = name;
}

std::string Entity::getName()
{
    return _name;
}

vector<unique_ptr<EntityState>>& Entity::get_states() {
    return _states;
}