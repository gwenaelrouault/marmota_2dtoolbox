#include "marmota_asset_store.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void MarmotaAssetStore::open(shared_ptr<MarmotaCache> cache, const filesystem::path &path)
{
    _logger.infoStream() << "Marmota:open(" << path << ")";
    cache->clear();
    sqlite3 *index_db = nullptr;
    int rc = sqlite3_open(path.c_str(), &index_db);
    if (rc)
    {
        _logger.infoStream() << "Marmota:open(" << path << ") - KO";
        sqlite3_close(index_db);
        throw DBException("Cannot open new project : cannot open metadata database");
    }
    _logger.infoStream() << "Marmota:open(" << path << ") - OK";
    char *err = nullptr;
    rc = sqlite3_exec(index_db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &err);
    if (rc)
    {
        sqlite3_close(index_db);
        throw DBException("Cannot open new project : cannot open metadata database");
    }
    _logger.infoStream() << "Marmota:open(" << path << ") - foreign_keys enabled";
    _db_index = make_index_db(index_db);
    _logger.infoStream() << "Marmota:open(" << path << ") - database created";
    create_tables();
    _logger.infoStream() << "Marmota:open(" << path << ") - [OK]";
}

void MarmotaAssetStore::load_level(shared_ptr<MarmotaCache> cache, const string &name)
{
    _logger.infoStream() << "Marmota:load level(" << name << ")";
    cache->clear();
    if (_table_level == nullptr || _table_level_sprite == nullptr)
    {
        throw DBException("Cannot load level : table level not created");
    }
    auto level = _table_level->load_level(name);
    _table_level_sprite->get_level_sprites(level);
    cache->_level = std::move(level);
    for (auto id : cache->_level->_sprites)
    {
        load_sprite(cache, id);
    }
    _logger.infoStream() << "Marmota:load level(" << name << ") - [OK]";
}

uint64_t MarmotaAssetStore::create_sprite(shared_ptr<MarmotaCache> cache)
{
    _logger.infoStream() << "Marmota:create_sprite";
    if (_table_sprite == nullptr)
    {
        throw DBException("Cannot create sprite : table sprite not created");
    }
    uint64_t new_id = _table_sprite->new_entity("NEW");
    auto default_level_id = _table_level->get_default_id();
    _table_level_sprite->add_sprite_to_level(new_id, default_level_id);
    _logger.infoStream() << "Marmota:create_sprite(" << new_id << ") - [OK]";
    load_sprite(cache, new_id);
    return new_id;
}

void MarmotaAssetStore::remove_sprite(shared_ptr<MarmotaCache> cache, uint64_t id)
{
    _logger.infoStream() << "Marmota:remove_sprite(" << id << ")";
    if (_table_sprite == nullptr)
    {
        throw DBException("Cannot remove sprite : table sprite not created");
    }
    _table_sprite->delete_item(id);
    if (cache->_sprites.contains(id))
    {
        cache->_sprites.erase(id);
    }
    _logger.infoStream() << "Marmota:remove_sprite(" << id << ") [OK]";
}

void MarmotaAssetStore::update_sprite(shared_ptr<MarmotaCache> cache, uint64_t id, const string &name)
{
    _logger.infoStream() << "Marmota:update_sprite(" << id << "," << name << ")";
    if (_table_sprite == nullptr)
    {
        throw DBException("Cannot update sprite : table sprite not created");
    }
    if (!cache->_sprites.contains(id))
    {
        throw DBException("Cannot update sprite : not exists sprite");
    }
    _table_sprite->update_entity(id, name);
    cache->_sprites[id]->_name = name;
    _logger.infoStream() << "Marmota:update_sprite(" << id << "," << name << ") [OK]";
}

void MarmotaAssetStore::delete_state(shared_ptr<MarmotaCache> cache, MarmotaId sprite_id, uint64_t id) {
    _logger.infoStream() << "Marmota:delete_state(" << sprite_id << "," << id << ")";
    if (_table_state == nullptr)
    {
        throw DBException("Cannot delete state : table state not created");
    }
    _table_state->delete_item(id);
    if (cache->_sprites.contains(sprite_id) && cache->_sprites[sprite_id]->_states.contains(id))
    {
        cache->_sprites[sprite_id]->_states.erase(id);
    }
    _logger.infoStream() << "Marmota:delete_state(" << id << ") [OK]";
}

uint64_t MarmotaAssetStore::create_state(shared_ptr<MarmotaCache> cache, MarmotaId sprite_id, const string &name)
{
    _logger.infoStream() << "Marmota:create_state(" << sprite_id << "," << name << ")";
    if (_table_state == nullptr)
    {
        throw DBException("Cannot create state : table state not created");
    }
    auto new_id = _table_state->new_entity(sprite_id, name);
    _logger.infoStream() << "Marmota:create_state(" << new_id << ") - [OK]";
    load_state(cache, sprite_id, new_id);
    return new_id;
}

uint64_t MarmotaAssetStore::create_frame(shared_ptr<MarmotaCache> cache, MarmotaId sprite_id, MarmotaId state_id, int num_frame)
{
    _logger.infoStream() << "Marmota:create_frame(" << state_id << ")";
    if (_table_frame == nullptr)
    {
        throw DBException("Cannot create state : table state not created");
    }
    auto new_id = _table_frame->new_entity(state_id, num_frame);
    _logger.infoStream() << "Marmota:create_frame(" << new_id << ") - [OK]";
    load_frame(cache, sprite_id, state_id, new_id);
    return 0;
}

void MarmotaAssetStore::load_frame(shared_ptr<MarmotaCache> cache, MarmotaId sprite_id, MarmotaId state_id, MarmotaId id)
{
    _logger.infoStream() << "Marmota:load_frame(" << id << ")";
    auto frame = _table_frame->load_frame(id);
    if (cache->_sprites.contains(sprite_id) && cache->_sprites[sprite_id]->_states.contains(state_id))
    {
        if (cache->_sprites[sprite_id]->_states[state_id]->_frames.contains(id))
        {
            cache->_sprites[sprite_id]->_states[state_id]->_frames[id]->update(frame);
        }
        else
        {
            cache->_sprites[sprite_id]->_states[state_id]->_frames[id] = std::move(frame);
        }
    }
}

void MarmotaAssetStore::load_sprite(shared_ptr<MarmotaCache> cache, MarmotaId id)
{
    _logger.infoStream() << "Marmota:load_sprite(" << id << ")";
    auto new_sprite = _table_sprite->load_sprite(id);
    bool updated = false;
    _table_state->load_states(new_sprite);
    for (auto state : new_sprite->_states)
    {
        _table_frame->load_frames(state.second);
    }
    for (auto sprite : cache->_sprites)
    {
        if (sprite.first == id)
        {
            sprite.second->update(new_sprite);
            updated = true;
            break;
        }
    }
    if (!updated)
    {
        cache->_sprites[id] = std::move(new_sprite);
    }
}

void MarmotaAssetStore::load_state(shared_ptr<MarmotaCache> cache, MarmotaId sprite_id, MarmotaId id)
{
    _logger.infoStream() << "Marmota:load_state(" << id << ")";
    auto new_state = _table_state->load_state(id);
    bool updated = false;
    _table_frame->load_frames(new_state);
    if (!cache->_sprites.contains(sprite_id))
    {
        throw DBException("No sprite");
    }
    for (auto state : cache->_sprites[sprite_id]->_states)
    {
        if (state.first == id)
        {
            state.second->update(new_state);
            updated = true;
            break;
        }
    }
    if (!updated)
    {
        cache->_sprites[sprite_id]->_states[id] = std::move(new_state);
    }
}

void MarmotaAssetStore::create_tables()
{
    _table_sprite = make_unique<TableSprite>(_logger, _db_index);
    _table_sprite->create();
    _table_state = make_unique<TableState>(_logger, _db_index);
    _table_state->create();
    _table_frame = make_unique<TableFrame>(_logger, _db_index);
    _table_frame->create();
    _table_level = make_unique<TableLevel>(_logger, _db_index);
    _table_level->create();
    _table_level_sprite = make_unique<TableLevelSprite>(_logger, _db_index);
    _table_level_sprite->create();
}
