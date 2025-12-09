#include "table_state.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void TableState::create() {
    const char* query = R"(
        CREATE TABLE IF NOT EXISTS state (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            loop  BOOLEAN NOT NULL DEFAULT 0,
            speed INTEGER NOT NULL DEFAULT 0,
            width  INTEGER NOT NULL DEFAULT 0,
            height INTEGER NOT NULL DEFAULT 0,
            sprite_id  INTEGER NOT NULL,
            FOREIGN KEY (sprite_id) REFERENCES sprite(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE  
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table[STATE]:created";
}

void TableState::load_states(shared_ptr<MarmotaSprite>& sprite) {
    sprite->_states.clear();
    const char *query = R"(
        SELECT id,name,loop,speed,width,height FROM state WHERE sprite_id = ?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, sprite->_id);

    while (run_query(stmt) == SQLITE_ROW) {
        uint64_t id = (uint64_t) sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        bool loop = sqlite3_column_int(stmt, 2) == 1;
        int width = sqlite3_column_int(stmt, 3);
        int height = sqlite3_column_int(stmt, 4);
        sprite->_states[id] = make_shared<MarmotaState>(name, id, loop, width, height);
    }
    release_query(stmt);
    _logger.infoStream() << "Marmota:Table[STATE]:loaded " << sprite->_states.size() << " states from table STATE for sprite (" << sprite->_id << ")";
}