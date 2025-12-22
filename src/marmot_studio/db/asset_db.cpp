#include "asset_db.h"
#include "create_sprite_event.h"
#include "update_sprite_event.h"
#include "delete_sprite_event.h"
#include "create_state_event.h"
#include "update_state_event.h"
#include "delete_state_event.h"
#include "init_event.h"

using namespace marmot::studio;

void AssetDB::create_new_sprite()
{
    lock_guard<mutex> lock(_mutex);
    {
        auto new_id = _store->create_sprite(_cache);
        _queue->push_event(make_unique<CreateSpriteEvt>(new_id));
    }
}

void AssetDB::create_new_frame(MarmotaId sprite_id, MarmotaId state_id, int num)
{
    lock_guard<mutex> lock(_mutex);
    {
        auto new_id = _store->create_frame(_cache, sprite_id, state_id, num);
        _queue->push_event(make_unique<CreateSpriteEvt>(new_id));
    }
}

void AssetDB::remove_sprite(MarmotaId id)
{
    lock_guard<mutex> lock(_mutex);
    {
        _store->remove_sprite(_cache, id);
        _queue->push_event(make_unique<DeleteSpriteEvt>(id));
    }
}

void AssetDB::create_new_state(MarmotaId id, const string &name)
{
    lock_guard<mutex> lock(_mutex);
    {
        auto new_id = _store->create_state(_cache, id, name);
        _queue->push_event(make_unique<CreateStateEvt>(id, new_id));
    }
}

void AssetDB::delete_state(MarmotaId sprite_id, MarmotaId id)
{
    lock_guard<mutex> lock(_mutex);
    {
        _store->delete_state(_cache, sprite_id, id);
        _queue->push_event(make_unique<DeleteStateEvt>(sprite_id, id));
    }
}

void AssetDB::update_sprite(MarmotaId id, const string &name)
{
    lock_guard<mutex> lock(_mutex);
    {
        _store->update_sprite(_cache, id, name);
        _queue->push_event(make_unique<UpdateSpriteEvt>(id));
    }
}

void AssetDB::open_db(const filesystem::path &path)
{
    lock_guard<mutex> lock(_mutex);
    {

        _store->open(_cache, path);
        _queue->push_event(make_unique<InitEvt>());
    }
}

void AssetDB::load_level(const std::string &level_name)
{
    lock_guard<std::mutex> lock(_mutex);
    {
        _store->load_level(_cache, level_name);
        _queue->push_event(make_unique<InitEvt>());
    }
}

bool AssetDB::get(map<uint64_t, unique_ptr<EditorSprite>> &sprites)
{
    bool updated = false;
    lock_guard<std::mutex> lock(_mutex);
    {
        auto evt = _queue->pop_event();
        if (evt != nullptr) {
            _logger.infoStream() << "MODEL:" << *evt.get();
            updated = evt->apply(sprites, _cache);
        }
    }
    return updated;
}