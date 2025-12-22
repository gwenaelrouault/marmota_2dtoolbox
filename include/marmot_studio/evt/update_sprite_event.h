#pragma once

#include "update_entity_event.h"

namespace marmot::studio
{
    class UpdateSpriteEvt : public UpdateEntityEvt
    {
    public:
        explicit UpdateSpriteEvt(MarmotaId id) : UpdateEntityEvt(E_SPRITE, M_CREATE, id) {}
        virtual ~UpdateSpriteEvt() {}

        bool apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        void print(std::ostream& os) const override;
    };
}