#include "table_entity.h"
#include "db_error.h"
using namespace marmot::marmota;

void TableEntity::create()
{
    const char *query = R"(
        CREATE TABLE IF NOT EXISTS entity (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table entity created";
}

int TableEntity::new_entity(const string &name)
{
    sqlite3_stmt *stmt;
    const char *query = R"(
        INSERT INTO entity (name) VALUES (?);
        )";
    if (sqlite3_prepare_v2(_db.get(), query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table entity:" << err << "\n";
        throw DBException(err);
    }
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        const char *err = sqlite3_errmsg(_db.get());
        _logger.errorStream() << "Marmota:Table entity:" << err << "\n";
        throw DBException(err);
    }
    else
    {
        sqlite3_int64 newId = sqlite3_last_insert_rowid(_db.get());
        _logger.infoStream() << "Marmota:Entity added (" << newId << ")";
        return (int)newId;
    }
}