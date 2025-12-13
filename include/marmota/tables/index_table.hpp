#pragma once

#include <log4cpp/Category.hh>
#include <memory>
#include <string>
#include "index_db.hpp"

namespace marmot::marmota
{
    using namespace std;

    class IndexTable
    {
    public:
        IndexTable(log4cpp::Category &logger, SQLiteDB db) : _logger(logger), _db(db) {}
        virtual ~IndexTable() {}

        virtual void create() = 0;

        void exec(std::string_view sql);

        sqlite3_stmt *prepare_query(const string &query);

        int run_query(sqlite3_stmt *query);

        void release_query(sqlite3_stmt *query);

        void raise_db_error(const string &table_name);

    protected:
        log4cpp::Category &_logger;
        SQLiteDB _db;
    };
}