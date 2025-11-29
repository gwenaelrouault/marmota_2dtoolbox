#include "marmota_asset_store.h"
#include "db_error.h"

using namespace marmot::marmota;

void MarmotaAssetStore::open(const filesystem::path &path)
{
    _logger.infoStream() << "Marmota:open(" << path << ")";
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
    _table_entity = make_unique<TableEntity>(_logger, _db_index);
    _table_entity->create();
    _table_state = make_unique<TableState>(_logger, _db_index);
    _table_state->create();
    _table_frame = make_unique<TableFrame>(_logger, _db_index);
    _table_frame->create();
}

int MarmotaAssetStore::create_sprite(const std::string &name)
{
    if (_table_entity == nullptr) {
        throw DBException("Cannot create sprite : table entity not created");
    }
    return _table_entity->new_entity(name);
}

int MarmotaAssetStore::create_state(int entity_id, const string &name)
{
}

int MarmotaAssetStore::create_frame(int state_id)
{
}
