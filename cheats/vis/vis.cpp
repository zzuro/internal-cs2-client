#include "vis.h"
#include "../../sdk/interfaces/engineclient.h"
#include "../../src/cache/cache.h"
#include "../../src/cache/player.h"
#include <iostream>

ImDrawList* vis::drawList = nullptr;

bool vis::DrawBoxESP = false;
bool vis::WeaponESP = false;
bool vis::EnableNoFlash = false;


void vis::NoFlash()
{
    if(!CEngineClient::Get()->IsInGame() || !vis::EnableNoFlash){
        return;
    }

    const auto& localplayer = CMatchCache::GetLocalPlayer();
    if(!localplayer){
        return;
    }

    localplayer->AntiFlash();
    
}

void vis::BoxESP()
{
    
    if(!CEngineClient::Get()->IsInGame() || !vis::DrawBoxESP){
        return;
    }

    const std::lock_guard<std::mutex> lock(CMatchCache::GetLock());
    const auto& cachedEntities = CMatchCache::GetCachedEntities();
    for (const auto& it : cachedEntities) {
        const auto& cachedEntity = it.second;
        if(cachedEntity->GetType() != CCachedBaseEntity::Type::PLAYER && cachedEntity->GetType() != CCachedBaseEntity::Type::GUN){
            continue;
        }
        
        
        if (!cachedEntity->CanDoESP()) {
            cachedEntity->InvalidateDrawInfo();
            continue;
        }
        cachedEntity->DrawESP();
    }
}


void vis::UpdateESP() {

     if(!CEngineClient::Get()->IsInGame() || !vis::DrawBoxESP){
        return;
    }

    const std::lock_guard<std::mutex> lock(CMatchCache::GetLock());

    const auto& cachedEntities = CMatchCache::GetCachedEntities();
    for (const auto& it : cachedEntities) {
        const auto& cachedEntity = it.second;

        
        if(cachedEntity->GetType() != CCachedBaseEntity::Type::PLAYER && cachedEntity->GetType() != CCachedBaseEntity::Type::GUN){
            continue;
        }
        
        
        if (!cachedEntity->CanDoESP()) {
            cachedEntity->InvalidateDrawInfo();
            continue;
        }

        cachedEntity->CalculateDrawInfo();
    }
}
