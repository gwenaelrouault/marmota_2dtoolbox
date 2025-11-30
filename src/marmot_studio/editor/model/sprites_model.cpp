#include "sprites_model.h"

using namespace marmot::studio;

void SpritesModel::add_sprite(unique_ptr<Entity> &item)
{
    _sprites.push_back(std::move(item));
}

void SpritesModel::create_sprite()
{
    auto sp = make_unique<Entity>();
    add_sprite(sp);
}

void SpritesModel::remove_sprite()
{
    _sprites.pop_back();
}

vector<unique_ptr<Entity>> &SpritesModel::get_sprites()
{
    return _sprites;
}

void SpritesModel::on_current_sprite(uint64_t id)
{
    _current_sprite = id;
}

void SpritesModel::on_no_sprite()
{
    _current_sprite = nullopt;
}

optional<uint64_t> SpritesModel::get_current_sprite()
{
    return _current_sprite;
}

void SpritesModel::set_sprite(marmota::Sprite &sprite)
{
    lock_guard<std::mutex> lock(_mutex);
    {
        for (auto &s : _sprites)
        {
            if (sprite._id == s.get()->_id) {
                s->set(sprite);
            }
        }
    }
}