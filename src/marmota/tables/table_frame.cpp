#include "table_frame.h"

using namespace marmot::marmota;

void TableFrame::create() {
    constexpr std::string_view query =
        "CREATE TABLE IF NOT EXISTS frame ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT"
        ");";
    exec(query);
}