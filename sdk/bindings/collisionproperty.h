#pragma once
#include "../../src/schema/schema.h"

class CCollisionProperty {
   public:
    SCHEMA(Vector, m_vecMins, "CCollisionProperty", "m_vecMins");
    SCHEMA(Vector, m_vecMaxs, "CCollisionProperty", "m_vecMaxs");
};