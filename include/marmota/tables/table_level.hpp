#pragma once

#include <optional>
#include "index_table.hpp"
#include "marmota_level.hpp"


namespace marmot::marmota
{

    constexpr string DEFAULT_LEVEL_NAME = "default";

    class TableLevel : public IndexTable
    {
    public:
        TableLevel(log4cpp::Category &logger, SQLiteDB db) : IndexTable(logger, db), _default_id(nullopt) {}
        virtual ~TableLevel() {}

        virtual void create() override;

        uint64_t add_level(const string& name);

        uint64_t get_default_id();

        virtual void delete_item(MarmotaId) override;

        shared_ptr<MarmotaLevel> load_level(const string& name);

    private:
        optional<MarmotaId> _default_id;
    };
}