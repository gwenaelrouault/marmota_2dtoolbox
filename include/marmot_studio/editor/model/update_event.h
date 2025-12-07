#pragma once

#include <cstdint>

namespace marmot::studio
{
    enum EntityType { E_LEVEL, E_SPRITE, E_STATE, E_FRAME};

    enum ModificationType { M_CREATE, M_UPDATE, M_DELETE};

    struct UpdateEvt {
        ModificationType _type;
        EntityType _entity;
        uint64_t _id;
    };
}