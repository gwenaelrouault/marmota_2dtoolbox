#pragma once

#include "index_table.hpp"
#include "marmota_level.hpp"

namespace marmot::marmota
{
    class TableLevelSprite : public IndexTable
    {
    public:
        TableLevelSprite(log4cpp::Category &logger, SQLiteDB db) : IndexTable(logger, db) {}
        virtual ~TableLevelSprite() {}

        virtual void create() override;

        MarmotaId add_sprite_to_level(MarmotaId sprite_id, MarmotaId level_id);

        void get_level_sprites(shared_ptr<MarmotaLevel> level);

        virtual void delete_item(MarmotaId id) override;
    };
}