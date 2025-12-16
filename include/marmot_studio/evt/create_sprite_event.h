#pragma once

#include "update_entity_event.h"

namespace marmot::studio
{
    class CreateSpriteEvt : public UpdateEntityEvt
    {
    public:
        explicit CreateSpriteEvt(uint64_t id) : UpdateEntityEvt(E_SPRITE, M_CREATE, id) {}
        virtual ~CreateSpriteEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        friend std::ostream& operator<<(std::ostream&, const CreateSpriteEvt&);

        void print(std::ostream& os) const override;
    };
} 