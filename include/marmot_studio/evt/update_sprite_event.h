#pragma once

#include "update_event.h"

namespace marmot::studio
{
    class UpdateSpriteEvt : public UpdateEvt
    {
    public:
        explicit UpdateSpriteEvt(uint64_t id) : UpdateEvt(E_SPRITE, M_CREATE, id) {}
        virtual ~UpdateSpriteEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;
    };
}