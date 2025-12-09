#include "index_table.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void IndexTable::exec(std::string_view sql)
{
    char *err = nullptr;
    int rc = sqlite3_exec(_db.get(), sql.data(), nullptr, nullptr, &err);
    if (rc != SQLITE_OK)
    {
        throw DBException(err);
    }
}

int IndexTable::run_query(sqlite3_stmt *query)
{
    return sqlite3_step(query);
}

void IndexTable::release_query(sqlite3_stmt *query)
{
    sqlite3_finalize(query);
}

void IndexTable::raise_db_error(const string &table_name)
{
    const char *err = sqlite3_errmsg(_db.get());
    _logger.errorStream() << "Marmota:Table[" << table_name << "]:" << err << "\n";
    throw DBException(err);
}

sqlite3_stmt *IndexTable::prepare_query(const string &query)
{
    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare_v2(_db.get(), query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        throw DBException(err);
    }
    return stmt;
}