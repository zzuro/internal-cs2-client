#pragma once
#include "../../src/schema/schema.h"

class CEntityIdentity {
   public:
    SCHEMA(uint32_t, m_flags, "CEntityIdentity", "m_flags");
};