#pragma once

#include "update_event.h"

namespace marmot::studio
{
    class UpdateEntityEvt : public UpdateEvt
    {
    public:
        UpdateEntityEvt(EntityType et, ModificationType mt, MarmotaId id) : UpdateEvt(et, mt), _id(id) {}
        virtual ~UpdateEntityEvt() {}

        virtual bool apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) = 0;

        MarmotaId get_id() const { return _id; }

    protected:
        MarmotaId _id;
    };
}