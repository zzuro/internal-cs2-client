
#include "gameentitysystem.h"
#include "gameresourceservice.h"

#include "../../src/signatures/sig.h"


CGameEntitySystem* CGameEntitySystem::Get() { return CGameResourceService::Get()->GetGameEntitySystem(); }

C_BaseEntity* CGameEntitySystem::GetBaseEntityInternal(int index) {
    return signatures::GetBaseEntity.GetPtr().Call<C_BaseEntity* (*)(void*, int)>(this, index);
}

int CGameEntitySystem::GetHighestEntityIndexInternal() {
    int highestIdx = -1;
    signatures::GetHighestEntityIndex.GetPtr().Call<void (*)(void*, int*)>(this, &highestIdx);
    return highestIdx;
}