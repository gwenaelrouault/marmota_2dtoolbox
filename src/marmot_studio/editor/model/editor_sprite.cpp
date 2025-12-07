#include "editor_sprite.h"

using namespace marmot::studio;

void EditorSprite::add_state(unique_ptr<EditorState> &item)
{
    _states.push_back(std::move(item));
}

void EditorSprite::create_new_state()
{
    auto new_state = make_unique<EditorState>(to_string(_index++));
    
    add_state(new_state);
}

void EditorSprite::remove_state()
{
    _states.pop_back();
}

vector<unique_ptr<EditorState>>& EditorSprite::get_states() {
    return _states;
}