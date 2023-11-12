#pragma once

#include "../../src/schema/schema.h"
#include "entityidentity.h"
#include "../types/handle.h"

class CSchemaClassInfo;

class CEntityInstance {
   public:
    CSchemaClassInfo* Schema_DynamicBinding();
    CBaseHandle GetRefEHandle();

    SCHEMA(CEntityIdentity*, m_pEntity, "CEntityInstance", "m_pEntity");
};