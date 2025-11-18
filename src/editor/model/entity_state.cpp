#include "entity_state.h"

using namespace marmot::studio;

string EntityState::get_name()
{
    return _name;
}

int EntityState::get_height()
{
    return _height;
}

int EntityState::get_width()
{
    return _width;
}

void EntityState::set_width(int width)
{
    _width = width;
}

void EntityState::set_height(int height)
{
    _height = height;
}