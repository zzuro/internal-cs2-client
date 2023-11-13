#define IMGUI_DEFINE_MATH_OPERATORS
#define M_PI 3.14159265358979323846
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
#include "../aim/aim.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"
#include <math.h>

ImDrawList *vis::drawList = nullptr;

bool vis::DrawBoxESP = false;
bool vis::WeaponESP = false;
bool vis::EnableNoFlash = false;
bool vis::EnableSkeletonESP = false;
bool vis::EnableHealth = false;
bool vis::EnableNames = false;

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

    if (!CEngineClient::Get()->IsInGame() || (!vis::DrawBoxESP && !vis::EnableHealth && !vis::EnableNames))
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

    if (!CEngineClient::Get()->IsInGame() || (!vis::DrawBoxESP && !vis::EnableHealth && !vis::EnableNames))
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


void vis::DrawFOV()
{
    if (!CEngineClient::Get()->IsInGame())
    {
        return;
    }
    ImVec2 screenCenter = ImGui::GetIO().DisplaySize / 2.f;
    float Radius = tan(aim::AimFOV / 180.f * M_PI / 2.f) / tan(90 / 180.f * M_PI / 2.f) * ImGui::GetIO().DisplaySize.x;
    
    drawList->AddCircle(screenCenter, Radius, IM_COL32(255, 255, 255, 255), 50 , 1.f);
}
