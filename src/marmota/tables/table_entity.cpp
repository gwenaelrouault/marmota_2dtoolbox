#include "table_entity.h"

using namespace marmot::marmota;

void TableEntity::create() {
    constexpr std::string_view query =
        "CREATE TABLE IF NOT EXISTS entity ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL"
        ");";
    exec(query);
}