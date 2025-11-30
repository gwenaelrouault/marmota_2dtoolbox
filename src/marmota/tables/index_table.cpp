#include "index_table.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void IndexTable::exec(std::string_view sql) {
    char* err = nullptr;
    int rc = sqlite3_exec(_db.get(), sql.data(), nullptr, nullptr, &err);
    if (rc != SQLITE_OK)
    {
        throw DBException(err);
    }
}