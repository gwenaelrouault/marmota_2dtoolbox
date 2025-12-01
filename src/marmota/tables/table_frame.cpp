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
    _logger.infoStream() << "Marmota:Table FRAME created";
}

void TableFrame::load_frames(vector<shared_ptr<MarmotaFrame>>& frames, uint64_t state_id) {
    frames.clear();

    // create query -----------------------------------------------------------
    sqlite3_stmt *stmt;
    const char *query = R"(
        SELECT id WHERE state_id = ?;
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table FRAME:" << err << "\n";
        throw DBException(err);
    }
    // complete query complete query with id-----------------------------------
    sqlite3_bind_int(stmt, 1, state_id);

    // fill vector with query result -------------------------------------------
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        uint64_t id = (uint64_t) sqlite3_column_int(stmt, 0);
        frames.push_back(make_shared<MarmotaFrame>(id));
    }
    sqlite3_finalize(stmt);
     _logger.infoStream() << "Marmota:Loaded " << frames.size() << " from table frame for FRAME (" << state_id << ")";
}