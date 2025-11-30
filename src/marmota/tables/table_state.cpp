#include "table_state.hpp"

using namespace marmot::marmota;

void TableState::create() {
    const char* query = R"(
        CREATE TABLE IF NOT EXISTS state (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            loop  BOOLEAN NOT NULL DEFAULT 0,
            speed INTEGER NOT NULL DEFAULT 0,
            width  BOOLEAN NOT NULL DEFAULT 0,
            height INTEGER NOT NULL DEFAULT 0,
            entity_id  INTEGER NOT NULL,
            FOREIGN KEY (entity_id) REFERENCES entity(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE  
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table state created";
}