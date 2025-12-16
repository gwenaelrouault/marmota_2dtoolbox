#include "table_level.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void TableLevel::create()
{
    const char *query = R"(
        CREATE TABLE IF NOT EXISTS level (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table[LEVEL]:created";

    sqlite3_stmt *stmt = prepare_query("SELECT 1 FROM level LIMIT 1;");
    if (run_query(stmt) == SQLITE_DONE)
    {
        _default_id = add_level(DEFAULT_LEVEL_NAME);
    }
    release_query(stmt);
}

shared_ptr<MarmotaLevel> TableLevel::load_level(const string& name) {
    const char *query = R"(
        SELECT id FROM level WHERE name=?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    if (run_query(stmt) == SQLITE_ROW)
    {
        MarmotaId id = sqlite3_column_int(stmt, 0);
        release_query(stmt);
        return make_shared<MarmotaLevel>(name, id);
    }
    release_query(stmt);
    throw DBException("No level");
}


MarmotaId TableLevel::add_level(const string &name)
{
    const char *query = R"(
        INSERT INTO level (name) VALUES (?);
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

    if (run_query(stmt) != SQLITE_DONE)
    {
        release_query(stmt);
        raise_db_error("LEVEL");
    }
    sqlite3_int64 newId = sqlite3_last_insert_rowid(_db.get());
    _logger.infoStream() << "Marmota:Table[LEVEL]:added (" << newId << ")";
    release_query(stmt);
    return (MarmotaId)newId;
}

MarmotaId TableLevel::get_default_id()
{
    if (!_default_id.has_value())
    {
        const char *query = R"(
            SELECT id FROM level WHERE name=?;
        )";
        sqlite3_stmt *stmt = prepare_query(query);
        sqlite3_bind_text(stmt, 1, DEFAULT_LEVEL_NAME.c_str(), -1, SQLITE_STATIC);
        if (run_query(stmt) == SQLITE_ROW)
        {
            _default_id = (MarmotaId)sqlite3_column_int64(stmt, 0);
        }
        else
        {
            throw DBException("No default level found");
        }
    }
    return _default_id.value();
}

void TableLevel::delete_item(MarmotaId id) {
    _logger.infoStream() << "Marmota:Table[LEVEL]:delete(" << id << ")";
}