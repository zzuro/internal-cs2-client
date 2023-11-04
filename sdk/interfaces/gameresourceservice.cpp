#include "gameresourceservice.h"
#include "../../src/memory/mem.h"
#include "../../src/utils/constants.h"

CGameResourceService* CGameResourceService::Get() {
    static const auto inst = mem::GetInterface(CConstants::ENGINE_LIB, "GameResourceServiceClientV001");
    return inst.Get<CGameResourceService*>();
}

CGameEntitySystem* CGameResourceService::GetGameEntitySystem() {
    return CPointer(this).GetField<CGameEntitySystem*>(0x58);
}