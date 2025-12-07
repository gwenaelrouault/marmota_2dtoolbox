#include "sprites_model.h"

using namespace marmot::studio;

void SpritesModel::add_sprite(unique_ptr<EditorSprite> &item)
{
    //_sprites.push_back(std::move(item));
}

void SpritesModel::create_sprite()
{
    auto sp = make_unique<EditorSprite>(12);
    add_sprite(sp);
}

void SpritesModel::remove_sprite()
{
    //_sprites.pop_back();
}

vector<unique_ptr<EditorSprite>> &SpritesModel::get_sprites()
{
    //return _sprites;
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

void SpritesModel::set_updated(bool flag)
{
    _flag_updated.store(flag);
}

bool SpritesModel::is_updated()
{
    return _flag_updated.load();
}

void SpritesModel::create_new_sprite()
{
    lock_guard<std::mutex> lock(_mutex);
    {
        auto id = _store->create_sprite(_db_cache);
        _evt_queue.push(make_unique<UpdateEvt>(UpdateEvt{M_CREATE, E_SPRITE, id}));
    }
}

void SpritesModel::update_sprite(uint64_t id, const string& name) {
    lock_guard<std::mutex> lock(_mutex);
    {
        _store->update_sprite(_db_cache, id, name);
        _evt_queue.push(make_unique<UpdateEvt>(UpdateEvt{M_UPDATE, E_SPRITE, id}));
    }
}

void SpritesModel::load_cache_from_db(const filesystem::path &path)
{
    lock_guard<std::mutex> lock(_mutex);
    {
        _store->open(_db_cache, path);
    }
}

bool SpritesModel::update_model_from_cache(map<uint64_t, unique_ptr<EditorSprite>>& sprites) {
    bool updated = false;
    lock_guard<std::mutex> lock(_mutex);
    {
        if (!_evt_queue.empty()) {
            auto evt = std::move(_evt_queue.back());
            _evt_queue.pop();
            if (evt->_type == M_DELETE) {
                if (evt->_entity == E_SPRITE) {
                    if (sprites.contains(evt->_id)) {
                        sprites.erase(evt->_id);
                        updated = true;
                    }
                }
            }
            else if (evt->_type == M_CREATE) {
                if (evt->_entity == E_SPRITE) {
                    if (!sprites.contains(evt->_id)) {
                        sprites[evt->_id] = make_unique<EditorSprite>(evt->_id);
                        updated = true;
                    }
                }
            }
            else {
                if (evt->_entity == E_SPRITE) {
                    if (sprites.contains(evt->_id)) {
                        sprites[evt->_id]->set(_db_cache->_sprites[evt->_id]);
                        updated = true;
                    }
                }
            }
        }
    }
    return updated;
}