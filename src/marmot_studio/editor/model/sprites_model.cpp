#include "sprites_model.h"

using namespace marmot::studio;

void SpritesModel::add_sprite(unique_ptr<Entity>& item) {
    _sprites.push_back(std::move(item));
}

void SpritesModel::create_sprite() {
    auto sp = make_unique<Entity>();
    add_sprite(sp);
}

void SpritesModel::remove_sprite() {
    _sprites.pop_back();
}

vector<unique_ptr<Entity>>& SpritesModel::get_sprites() {
    return _sprites;
}