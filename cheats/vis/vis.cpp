#include "vis.h"
#include "../../sdk/interfaces/engineclient.h"
#include "../../src/cache/cache.h"
#include <iostream>

bool vis::DrawBoxESP = false;
void vis::BoxESP()
{
    
    if(!CEngineClient::Get()->IsInGame() || !vis::DrawBoxESP){
        return;
    }

   
    const auto& cachedEntities = CMatchCache::GetCachedEntities();
    for (const auto& it : cachedEntities) {
        const auto& cachedEntity = it.second;
        if(cachedEntity->GetType() != CCachedBaseEntity::Type::PLAYER){
            continue;
        }
        
        
        if (!cachedEntity->CanDoESP()) {
            cachedEntity->InvalidateDrawInfo();
            continue;
        }
        std::cout << "Drawing box esp" << std::endl;
        /*cachedEntity->DrawESP();*/
    }
}