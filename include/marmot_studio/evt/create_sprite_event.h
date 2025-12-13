#pragma once

#include "update_event.h"

namespace marmot::studio
{
    class CreateSpriteEvt : public UpdateEvt
    {
    public:
        explicit CreateSpriteEvt(uint64_t id) : UpdateEvt(E_SPRITE, M_CREATE, id) {}
        virtual ~CreateSpriteEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;
    };
}