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

MarmotaId TableLevelSprite::add_sprite_to_level(MarmotaId sprite_id, MarmotaId level_id)
{
    _logger.infoStream() << "Marmota:Table[LEVEL_SPRITE]:update(" << sprite_id << "," << level_id << ")";
    MarmotaId id = 0;
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
        id = (MarmotaId)newId;
    }
    return id;
}

void TableLevelSprite::get_level_sprites(shared_ptr<MarmotaLevel> level)
{
    _logger.infoStream() << "Marmota:Table[LEVEL_SPRITE]:get_level_sprites(" << level->_name << "," << level->_id << ")";
    level->_sprites.clear();
    const char *query = R"(
        SELECT sprite_id FROM level_sprite WHERE level_id=?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, level->_id);
    while (run_query(stmt) == SQLITE_ROW)
    {
        level->_sprites.push_back((MarmotaId) sqlite3_column_int(stmt, 0));
    }
    release_query(stmt);
}

void TableLevelSprite::delete_item(MarmotaId id)
{
    _logger.infoStream() << "Marmota:Table[LEVEL_SPRITE]:delete(" << id << ")";
}