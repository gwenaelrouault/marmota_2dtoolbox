#pragma once

#include "index_table.hpp"
#include "marmota_sprite.hpp"
#include "table_state.hpp"
#include <cstdint>

namespace marmot::marmota
{
    class TableSprite : public IndexTable
    {
    public:
        TableSprite(log4cpp::Category &logger, SQLiteDB db) : IndexTable(logger, db) {}
        virtual ~TableSprite() {}

        virtual void create() override;

        MarmotaId new_entity(const string& name);

        void update_entity(MarmotaId id, const string& name);

        void load_sprites(vector<shared_ptr<MarmotaSprite>>& sprites);

        shared_ptr<MarmotaSprite> load_sprite(MarmotaId id);

        virtual void delete_item(MarmotaId id) override;
    };
}