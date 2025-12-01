#include "table_entity.hpp"
#include "db_error.hpp"
using namespace marmot::marmota;

void TableEntity::create()
{
    const char *query = R"(
        CREATE TABLE IF NOT EXISTS entity (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table entity created";
}

uint64_t TableEntity::new_entity(const string &name)
{
    sqlite3_stmt *stmt;
    const char *query = R"(
        INSERT INTO entity (name) VALUES (?);
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table ENTITY:" << err << "\n";
        throw DBException(err);
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table ENTITY:" << err << "\n";
        throw DBException(err);
    }
    else
    {
        sqlite3_int64 newId = sqlite3_last_insert_rowid(_db.get());
        _logger.infoStream() << "Marmota:Table ENTITY added (" << newId << ")";
        return (uint64_t)newId;
    }
}

void TableEntity::load_sprites(vector<shared_ptr<MarmotaSprite>>& sprites) {
    sprites.clear();
    // create query -----------------------------------------------------------
    sqlite3_stmt *stmt;
    const char *query = R"(
        SELECT id, name FROM entity;
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table entity:" << err << "\n";
        throw DBException(err);
    }
    // fill vector with query result -------------------------------------------
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        uint64_t id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        sprites.push_back(make_shared<MarmotaSprite>(name, id));
    }
    sqlite3_finalize(stmt);
}