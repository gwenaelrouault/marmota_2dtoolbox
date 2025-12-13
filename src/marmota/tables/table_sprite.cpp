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
    uint64_t id = 0;
    const char *query = R"(
        INSERT INTO sprite (name) VALUES (?);
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

    if (run_query(stmt) != SQLITE_DONE)
    {
        release_query(stmt);
        raise_db_error("sprite");
    }
    else
    {
        sqlite3_int64 newId = sqlite3_last_insert_rowid(_db.get());
        _logger.infoStream() << "Marmota:Table[SPRITE]:added (" << newId << ")";
        release_query(stmt);
        id = (uint64_t)newId;
    }
    return id;
}

void TableSprite::update_entity(uint64_t id, const string &name)
{
    _logger.infoStream() << "Marmota:Table[SPRITE]:update(" << id << "," << name << ")";
    const char *query = R"(
        UPDATE sprite SET name = ? WHERE id = ?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(id));
    _logger.infoStream() << "Marmota:Table[SPRITE]:query(" << sqlite3_sql(stmt) << ")";

    if (run_query(stmt) != SQLITE_DONE)
    {
        release_query(stmt);
        raise_db_error("sprite");
    }
    release_query(stmt);
}

void TableSprite::load_sprites(vector<shared_ptr<MarmotaSprite>> &sprites)
{
    sprites.clear();
    const char *query = R"(
        SELECT id, name FROM sprite;
        )";
    sqlite3_stmt *stmt = prepare_query(query);

    while (run_query(stmt) == SQLITE_ROW)
    {
        uint64_t id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        sprites.push_back(make_shared<MarmotaSprite>(name, id));
    }
    release_query(stmt);
}

shared_ptr<MarmotaSprite> TableSprite::load_sprite(uint64_t id)
{
    const char *query = R"(
        SELECT id, name FROM sprite WHERE id=?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, id);
    if (run_query(stmt) == SQLITE_ROW)
    {
        uint64_t id = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        release_query(stmt);
        return make_shared<MarmotaSprite>(name, id);
    }
    release_query(stmt);
    throw DBException("No sprite");
}