#pragma once

#include <ostream>
#include "update_event.h"

namespace marmot::studio
{
    class CreateSpriteEvt : public UpdateEvt
    {
    public:
        explicit CreateSpriteEvt(uint64_t id) : UpdateEvt(E_SPRITE, M_CREATE, id) {}
        virtual ~CreateSpriteEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        friend std::ostream& operator<<(std::ostream&, const CreateSpriteEvt&);

        void print(std::ostream& os) const override;
    };
} 