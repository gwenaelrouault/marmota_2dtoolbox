#include "sprites_model.h"

#include "create_sprite_event.h"
#include "update_sprite_event.h"
#include "delete_sprite_event.h"
#include "create_state_event.h"
#include "update_state_event.h"
#include "delete_state_event.h"
#include "init_event.h"

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
        auto new_id = _store->create_sprite(_db_cache);
        _evt_queue.push(make_unique<CreateSpriteEvt>(new_id));
    }
}

void SpritesModel::create_new_frame(MarmotaId sprite_id, MarmotaId state_id, int num) {
    lock_guard<std::mutex> lock(_mutex);
    {
        //auto new_id = _store->create_frame(_db_cache, sprite_id, num);
        //_evt_queue.push(make_unique<CreateSpriteEvt>(new_id));
    }
}

void SpritesModel::remove_sprite(uint64_t id)
{
    lock_guard<std::mutex> lock(_mutex);
    {
        _store->remove_sprite(_db_cache, id);
        _evt_queue.push(make_unique<DeleteSpriteEvt>(id));
    }
}


void SpritesModel::create_new_state(uint64_t id, const string &name)
{
    lock_guard<std::mutex> lock(_mutex);
    {
        auto new_id = _store->create_state(_db_cache, id, name);
        _evt_queue.push(make_unique<CreateStateEvt>(id, new_id));
    }
}

void SpritesModel::update_sprite(uint64_t id, const string &name)
{
    lock_guard<std::mutex> lock(_mutex);
    {
        _store->update_sprite(_db_cache, id, name);
        _evt_queue.push(make_unique<UpdateSpriteEvt>(id));
    }
}

void SpritesModel::open_db(const filesystem::path &path)
{
    lock_guard<std::mutex> lock(_mutex);
    {
        _store->open(_db_cache, path);
        _evt_queue.push(make_unique<InitEvt>());
    }
}

void SpritesModel::load_level(const std::string& level_name) {
    lock_guard<std::mutex> lock(_mutex);
    {
        _store->load_level(_db_cache, level_name);
        _evt_queue.push(make_unique<InitEvt>());
    }
}

bool SpritesModel::update_model_from_cache(map<uint64_t, unique_ptr<EditorSprite>> &sprites)
{
    bool updated = false;
    lock_guard<std::mutex> lock(_mutex);
    {
        if (!_evt_queue.empty())
        {
            auto evt = std::move(_evt_queue.back());
            _logger.infoStream() << "MODEL:" << *evt.get();
            _evt_queue.pop();
            updated = evt->apply(sprites, _db_cache);
        }
    }
    return updated;
}