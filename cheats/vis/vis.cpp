#include "vis.h"
#include "../../sdk/interfaces/engineclient.h"
#include "../../sdk/bindings/modelstate.h"
#include "../../sdk/bindings/baseentity.h"
#include "../../sdk/bindings/playercontroller.h"
#include "../../sdk/bindings/playerpawn.h"
#include "../../src/cache/cache.h"
#include "../../src/cache/player.h"
#include "../../src/math/math.h"
#include <iostream>

ImDrawList *vis::drawList = nullptr;

bool vis::DrawBoxESP = false;
bool vis::WeaponESP = false;
bool vis::EnableNoFlash = false;
bool vis::EnableSkeletonESP = false;

void vis::NoFlash()
{
    if (!CEngineClient::Get()->IsInGame() || !vis::EnableNoFlash)
    {
        return;
    }

    const auto &localplayer = CMatchCache::GetLocalPlayer();
    if (!localplayer)
    {
        return;
    }

    localplayer->AntiFlash();
}

void vis::BoxESP()
{

    if (!CEngineClient::Get()->IsInGame() || !vis::DrawBoxESP)
    {
        return;
    }

    const std::lock_guard<std::mutex> lock(CMatchCache::GetLock());
    const auto &cachedEntities = CMatchCache::GetCachedEntities();
    for (const auto &it : cachedEntities)
    {
        const auto &cachedEntity = it.second;
        if (cachedEntity->GetType() != CCachedBaseEntity::Type::PLAYER && cachedEntity->GetType() != CCachedBaseEntity::Type::GUN)
        {
            continue;
        }

        if (!cachedEntity->CanDoESP())
        {
            cachedEntity->InvalidateDrawInfo();
            continue;
        }
        cachedEntity->DrawESP();
    }
}

void vis::UpdateESP()
{

    if (!CEngineClient::Get()->IsInGame() || !vis::DrawBoxESP)
    {
        return;
    }

    const std::lock_guard<std::mutex> lock(CMatchCache::GetLock());

    const auto &cachedEntities = CMatchCache::GetCachedEntities();
    for (const auto &it : cachedEntities)
    {
        const auto &cachedEntity = it.second;

        if (cachedEntity->GetType() != CCachedBaseEntity::Type::PLAYER && cachedEntity->GetType() != CCachedBaseEntity::Type::GUN)
        {
            continue;
        }

        if (!cachedEntity->CanDoESP())
        {
            cachedEntity->InvalidateDrawInfo();
            continue;
        }

        cachedEntity->CalculateDrawInfo();
    }
}

void vis::SkeletonESP()
{
    if (!CEngineClient::Get()->IsInGame() || !vis::EnableSkeletonESP)
    {
        return;
    } 

    const auto &localplayer = CMatchCache::GetLocalPlayer();
    const std::lock_guard<std::mutex> lock(CMatchCache::GetLock());
    const auto &cachedEntities = CMatchCache::GetCachedEntities();
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

        CCachedPlayer *player = reinterpret_cast<CCachedPlayer *>(cachedEntity.get());
        if (!player && (player != localplayer))
        {
            continue;
        }

        CCSPlayerController *controller = player->Get();
        if (!controller || controller->m_bIsLocalPlayerController())
        {
            continue;
        }

        C_CSPlayerPawnBase *pawn = controller->m_hPlayerPawn().Get();

        if (!pawn )
        {
            continue;
        }

        CGameSceneNode *node = pawn->m_pGameSceneNode();

        if (!node)
        {
            continue;
        }

        CModelState modelState = node->m_modelState();
        CBoneData *boneArray = modelState.m_boneArray;

        CBoneData Previous, Current;
        for (auto i : BoneJointList::List)
        {
            Previous.Location = Vector(0, 0, 0);
            for (auto Index : i)
            {
                Current = boneArray[Index];
                if (Previous.Location.isZero())
                {
                    Previous = Current;
                    continue;
                }

                ImVec2 curr, prev;
                if (CMath::Get().WorldToScreen(Current.Location, curr) && CMath::Get().WorldToScreen(Previous.Location, prev))
                {
                    drawList->AddLine(prev, curr, IM_COL32(255, 255, 255, 255), 1.0f);
                }
                Previous = Current;
            }
        }
    }
}
