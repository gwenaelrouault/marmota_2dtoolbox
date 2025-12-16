#pragma once

#include <ostream>
#include "update_event.h"

namespace marmot::studio
{
    class InitEvt : public UpdateEvt
    {
    public:
        explicit InitEvt() : UpdateEvt(E_ALL, M_CREATE) {}
        virtual ~InitEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        friend std::ostream& operator<<(std::ostream&, const InitEvt&);

        void print(std::ostream& os) const override;
    };
}