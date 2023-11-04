#include "entityinstance.h"
#include "../../src/virtual/virtual.h"

CSchemaClassInfo* CEntityInstance::Schema_DynamicBinding() {
    CSchemaClassInfo* binding = nullptr;
    vt::CallMethod<void>(this, 34, &binding);
    return binding;
}

CBaseHandle CEntityInstance::GetRefEHandle() {
    CBaseHandle handle{};

    CEntityIdentity* identity = m_pEntity();
    if (!identity) return handle;

    CBaseHandle unkHandle = CPointer(identity).GetField<CBaseHandle>(0x10);
    handle.Init(unkHandle.GetEntryIndex(), unkHandle.GetSerialNumber() - (identity->m_flags() & 1));

    return handle;
}