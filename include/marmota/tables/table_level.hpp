#pragma once

#include <cstdint>
#include <optional>
#include "index_table.hpp"


namespace marmot::marmota
{

    constexpr string DEFAULT_LEVEL_NAME = "default";

    class TableLevel : public IndexTable
    {
    public:
        TableLevel(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db), _default_id(nullopt) {}
        virtual ~TableLevel() {}

        virtual void create();

        uint64_t add_level(const string& name);

        uint64_t get_default_id();

    private:
        optional<uint64_t> _default_id;
    };
}