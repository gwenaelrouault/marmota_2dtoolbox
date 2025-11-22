#include "index_table.h"
#include "db_error.h"

using namespace marmot::marmota;

void IndexTable::exec(std::string_view sql) {
    char* err = nullptr;
    int rc = sqlite3_exec(_db.get(), sql.data(), nullptr, nullptr, &err);
    if (rc != SQLITE_OK)
    {
        throw DBException(err);
    }
}