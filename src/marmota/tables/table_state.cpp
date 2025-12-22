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

void TableState::load_states(shared_ptr<MarmotaSprite> sprite) {
    _logger.infoStream() << "Marmota:Table[STATE]:load all for sprite(" << sprite->_id << ")";
    sprite->_states.clear();
  
    const char *query = R"(
        SELECT id,name,loop,speed,width,height FROM state WHERE sprite_id = ?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, sprite->_id);

    while (run_query(stmt) == SQLITE_ROW) {
       _logger.infoStream()<<"QUERY1";
        auto state = make_state_from_result(stmt);
         _logger.infoStream()<<"QUERY";
         auto key = state->_id;
        sprite->_states[key] = state;
        _logger.infoStream()<<"QUERY2";
    }
     _logger.infoStream()<<"QUERY3";
    release_query(stmt);
 
    _logger.infoStream() << "Marmota:Table[STATE]:loaded " << sprite->_states.size() << " states from table STATE for sprite (" << sprite->_id << ")";
}

MarmotaId TableState::new_entity(MarmotaId sprite_id, const string &name) {
    _logger.infoStream() << "Marmota:Table[STATE]:new(" << name << ")";
    const char *query = R"(
        INSERT INTO state (name,sprite_id) VALUES (?,?);
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(sprite_id));
    if (run_query(stmt) != SQLITE_DONE)
    {
        release_query(stmt);
        raise_db_error("sprite");
    }
    sqlite3_int64 newId = sqlite3_last_insert_rowid(_db.get());
    _logger.infoStream() << "Marmota:Table[STATE]:added (" << newId << ")";
    release_query(stmt);
    return (MarmotaId)newId;
}

shared_ptr<MarmotaState> TableState::load_state(MarmotaId id) {
    _logger.infoStream() << "Marmota:Table[STATE]:load(" << id << ")";
    const char *query = R"(
        SELECT id,name,loop,speed,width,height FROM state WHERE id=?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, id);
    if (run_query(stmt) == SQLITE_ROW)
    {
        return make_state_from_result(stmt);
    }
    release_query(stmt);
    throw DBException("No sprite");
}

shared_ptr<MarmotaState> TableState::make_state_from_result(sqlite3_stmt *stmt) {
    auto id = (MarmotaId) sqlite3_column_int(stmt, 0);
    string name;
    const char* n = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    if (n != nullptr) {
        name = n;
    }
    bool loop = sqlite3_column_int(stmt, 2) != 0;
    int speed = sqlite3_column_int(stmt, 3) != 0;
    int width = sqlite3_column_int(stmt, 4) != 0;
    int height = sqlite3_column_int(stmt, 5) != 0;
    auto loaded = make_shared<MarmotaState>(name, id, loop, speed, width, height);
    _logger.infoStream() << "Marmota:Table[STATE]:loaded(" << loaded << ")";
    return std::move(loaded);
}

void TableState::delete_item(MarmotaId id) {
    _logger.infoStream() << "Marmota:Table[STATE]:delete(" << id << ")";
}