#include "table_level_sprite.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void TableLevelSprite::create()
{
    const char *query = R"(
        CREATE TABLE IF NOT EXISTS level_sprite (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            sprite_id  INTEGER NOT NULL,
            level_id  INTEGER NOT NULL,
            FOREIGN KEY (sprite_id) REFERENCES sprite(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE,
            FOREIGN KEY (level_id) REFERENCES level(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE  
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table[LEVEL_SPRITE]:created";
}

uint64_t TableLevelSprite::add_sprite_to_level(uint64_t sprite_id, uint64_t level_id)
{
    _logger.infoStream() << "Marmota:Table[LEVEL_SPRITE]:update(" << sprite_id << "," << level_id << ")";
    const char *query = R"(
        INSERT INTO level_sprite (sprite_id,level_id) VALUES (?,?);
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int64(stmt, 1, static_cast<sqlite3_int64>(sprite_id));
    sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(level_id));
    _logger.infoStream() << "Marmota:Table[LEVEL_SPRITE]:query(" << sqlite3_sql(stmt) << ")";
    if (run_query(stmt) != SQLITE_DONE)
    {
        release_query(stmt);
        raise_db_error("LEVEL_SPRITE");
    }
    else
    {
        sqlite3_int64 newId = sqlite3_last_insert_rowid(_db.get());
        _logger.infoStream() << "Marmota:Table[LEVEL_SPRITE]:added (" << newId << ")";
        release_query(stmt);
        return (uint64_t)newId;
    }
}