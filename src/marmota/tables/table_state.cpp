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
            entity_id  INTEGER NOT NULL,
            FOREIGN KEY (entity_id) REFERENCES entity(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE  
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table STATE created";
}

void TableState::load_states(vector<shared_ptr<MarmotaState>>& states, uint64_t entity_id) {
    states.clear();
    // create query -----------------------------------------------------------
    sqlite3_stmt *stmt;
    const char *query = R"(
        SELECT id,name,loop,speed,width,height FROM entity WHERE entity_id = ?;
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table entity:" << err << "\n";
        throw DBException(err);
    }
    // complete query complete query with id-----------------------------------
    sqlite3_bind_int(stmt, 1, entity_id);

    // fill vector with query result -------------------------------------------
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        uint64_t id = (uint64_t) sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        bool loop = sqlite3_column_int(stmt, 2) == 1;
        int width = sqlite3_column_int(stmt, 3);
        int height = sqlite3_column_int(stmt, 4);
        states.push_back(make_shared<MarmotaState>(name, id, loop, width, height));
    }
    sqlite3_finalize(stmt);
    _logger.infoStream() << "Marmota:Loaded " << states.size() << " from table STATE for sprite (" << entity_id << ")";
}