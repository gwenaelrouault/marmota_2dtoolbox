#pragma once

#include "update_entity_event.h"

namespace marmot::studio
{
    class CreateFrameEvt : public UpdateEntityEvt
    {
    public:
        explicit CreateFrameEvt(MarmotaId sprite_id, MarmotaId state_id, MarmotaId id, int num) 
            : UpdateEntityEvt(E_SPRITE, M_CREATE, id), _sprite_id(sprite_id), _state_id(state_id), _num(num) {}
        virtual ~CreateFrameEvt() {}

        bool apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        friend std::ostream& operator<<(std::ostream&, const CreateFrameEvt&);

        void print(std::ostream& os) const override;
        private:
            MarmotaId _sprite_id;
            MarmotaId _state_id;
            int _num;
    };
} 