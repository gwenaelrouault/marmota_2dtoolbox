#include "table_frame.h"

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
    _logger.infoStream() << "Marmota:Table frame created";
}