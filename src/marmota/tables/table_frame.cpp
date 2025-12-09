#include "table_frame.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void TableFrame::create() {
    const char* query = R"(
        CREATE TABLE IF NOT EXISTS frame (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            num INTEGER NOT NULL DEFAULT 0,
            state_id  INTEGER NOT NULL,
            FOREIGN KEY (state_id) REFERENCES state(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE  
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table[FRAME]:created";
}

void TableFrame::load_frames(shared_ptr<MarmotaState>& state) {
    state->_frames.clear();
    // create query -----------------------------------------------------------
    const char *query = R"(
        SELECT id WHERE state_id = ?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, state->_id);
    
    // fill vector with query result -------------------------------------------
    while (run_query(stmt) == SQLITE_ROW) {
        uint64_t id = (uint64_t) sqlite3_column_int(stmt, 0);
        state->_frames[id] = make_shared<MarmotaFrame>(id);
    }
    release_query(stmt);
     _logger.infoStream() << "Marmota:Table[FRAME]:Loaded " << state->_frames.size() << " from table frame for FRAME (" << state->_id << ")";
}