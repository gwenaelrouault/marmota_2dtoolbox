#include "table_sprite.hpp"
#include "db_error.hpp"
using namespace marmot::marmota;

void TableSprite::create()
{
    const char *query = R"(
        CREATE TABLE IF NOT EXISTS sprite (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table[SPRITE]:created";
}

uint64_t TableSprite::new_entity(const string &name)
{
    _logger.infoStream() << "Marmota:Table[SPRITE]:new(" << name << ")";
    sqlite3_stmt *stmt = nullptr;
    const char *query = R"(
        INSERT INTO sprite (name) VALUES (?);
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table[SPRITE]:" << err << "\n";
        throw DBException(err);
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table[SPRITE]:" << err << "\n";
        sqlite3_finalize(stmt);
        throw DBException(err);
    }
    else
    {
        sqlite3_int64 newId = sqlite3_last_insert_rowid(_db.get());
        _logger.infoStream() << "Marmota:Table[SPRITE]:added (" << newId << ")";
        sqlite3_finalize(stmt);
        return (uint64_t)newId;
    }
}

void TableSprite::update_entity(uint64_t id, const string& name) {
     _logger.infoStream() << "Marmota:Table[SPRITE]:update(" << id << "," << name << ")";
    sqlite3_stmt *stmt = nullptr;
    const char *query = R"(
        UPDATE sprite SET name = ? WHERE id = ?;
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table[SPRITE]:" << err << "\n";
        throw DBException(err);
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(id));
    _logger.infoStream() << "Marmota:Table[SPRITE]:query(" << sqlite3_sql(stmt) << ")";
     _logger.infoStream() << "Marmota:Table[SPRITE]:update execute";
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        const char *err = sqlite3_errmsg(_db.get());
        sqlite3_finalize(stmt);
        throw DBException(err);
    }
    sqlite3_finalize(stmt);
}

void TableSprite::load_sprites(vector<shared_ptr<MarmotaSprite>>& sprites) {
    sprites.clear();
    // create query -----------------------------------------------------------
    sqlite3_stmt *stmt;
    const char *query = R"(
        SELECT id, name FROM sprite;
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table[SPRITE]:" << err << "\n";
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

shared_ptr<MarmotaSprite> TableSprite::load_sprite(uint64_t id) {
    // create query -----------------------------------------------------------
    sqlite3_stmt *stmt;
    const char *query = R"(
        SELECT id, name FROM sprite WHERE id=?;
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table[SPRITE]:" << err << "\n";
        throw DBException(err);
    }
    // complete query complete query with id-----------------------------------
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        uint64_t id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        sqlite3_finalize(stmt);
        return make_shared<MarmotaSprite>(name, id);
    }
    sqlite3_finalize(stmt);
    return nullptr;
}