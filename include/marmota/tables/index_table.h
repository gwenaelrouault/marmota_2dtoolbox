#pragma once

#include <log4cpp/Category.hh>
#include <memory>
#include "index_db.h"

namespace marmot::marmota
{
    using namespace std;

    class IndexTable
    {
    public:
        IndexTable(log4cpp::Category &logger, SQLiteDB& db) : _logger(logger), _db(db) {}
        virtual ~IndexTable() {}
        
        virtual void create() = 0;

        void exec(std::string_view sql);

    protected:
        log4cpp::Category &_logger;
        SQLiteDB& _db;
    };
}