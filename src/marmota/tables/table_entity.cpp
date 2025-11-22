#include "table_entity.h"

using namespace marmot::marmota;

void TableEntity::create() {
    const char* query = R"(
        CREATE TABLE IF NOT EXISTS entity (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            );
        )";
    exec(query);
}