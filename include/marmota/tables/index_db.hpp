#pragma once

#include <memory>
#include <sqlite3.h>

namespace marmot::marmota
{

    struct SQLiteDeleter
    {
        void operator()(sqlite3 *db) const noexcept
        {
            if (db)
            {
                sqlite3_close(db);
            }
        }
    };

    using SQLiteDB = std::shared_ptr<sqlite3>;

    inline SQLiteDB make_index_db(sqlite3 *db) {
        return SQLiteDB(db, SQLiteDeleter{});
    }
}
