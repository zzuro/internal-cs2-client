#include "aim.h"
#include "../../sdk/interfaces/engineclient.h"
#include "../../sdk/bindings/playercontroller.h"
#include "../../src/cache/cache.h"
#include "../../src/cache/player.h"

bool aim::EnableAimBot = false;

void aim::AimBot()
{
    if (!CEngineClient::Get()->IsInGame() || !EnableAimBot)
    {
        return;
    }

    const std::lock_guard<std::mutex> lock(CMatchCache::GetLock());
    const auto &cachedEntities = CMatchCache::GetCachedEntities();

    const auto &localplayer = CMatchCache::GetLocalPlayer();
    if (!localplayer)
    {
        return;
    }

    auto bestFov = 150.f;

    for (const auto &it : cachedEntities)
    {
        const auto &cachedEntity = it.second;
        if (cachedEntity->GetType() != CCachedBaseEntity::Type::PLAYER)
        {
            continue;
        }

        if (!cachedEntity->CanDoESP())
        {

            continue;
        }

        CCachedPlayer *cachedPlayer = dynamic_cast<CCachedPlayer *>(cachedEntity.get());
        if (!cachedPlayer)
        {
            continue;
        }

        if (cachedPlayer->IsLocalPlayer() || cachedPlayer->GetTeam() != localplayer->GetTeam())
        {
            continue;
        }

        CCSPlayerController *controller = cachedPlayer->Get();
        if (!controller)
        {
            continue;
        }

        if (!controller->m_bPawnIsAlive())
        {
            continue;
        }


    }
}
