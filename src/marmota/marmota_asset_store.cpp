#include "marmota_asset_store.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void MarmotaAssetStore::open(shared_ptr<MarmotaCache>& cache, const filesystem::path &path)
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
    _table_sprite = make_unique<TableSprite>(_logger, _db_index);
    _table_sprite->create();
    _table_state = make_unique<TableState>(_logger, _db_index);
    _table_state->create();
    _table_frame = make_unique<TableFrame>(_logger, _db_index);
    _table_frame->create();
    _logger.infoStream() << "Marmota:open(" << path << ") - database initialized";
}

uint64_t MarmotaAssetStore::create_sprite(shared_ptr<MarmotaCache>& cache)
{
    _logger.infoStream() << "Marmota:create_sprite";
    if (_table_sprite == nullptr) {
        throw DBException("Cannot create sprite : table sprite not created");
    }
    uint64_t new_id = _table_sprite->new_entity("NEW");
    _logger.infoStream() << "Marmota:create_sprite(" << new_id << ") [OK]";
    load_sprite(cache, new_id);
    return new_id;
}

void MarmotaAssetStore::update_sprite(shared_ptr<MarmotaCache>& cache, uint64_t id, const string& name) {
    _logger.infoStream() << "Marmota:update_sprite(" << id << "," << name << ")";
    if (_table_sprite == nullptr) {
        throw DBException("Cannot update sprite : table sprite not created");
    }
    if (!cache->_sprites.contains(id)) {
        throw DBException("Cannot update sprite : not exists sprite");
    }
    _table_sprite->update_entity(id, name);
    cache->_sprites[id]->_name = name;
    _logger.infoStream() << "Marmota:update_sprite(" << id << "," << name << ") [OK]";
}

int MarmotaAssetStore::create_state(int entity_id, const string &name)
{
}

int MarmotaAssetStore::create_frame(int state_id)
{
}

void MarmotaAssetStore::load_sprite(shared_ptr<MarmotaCache>& cache, uint64_t id)
{
    _logger.infoStream() << "Marmota:load_sprite(" << id << ")";
    auto new_sprite = _table_sprite->load_sprite(id);
    if (new_sprite == nullptr)
    {
        throw DBException("No sprite");
    }
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
