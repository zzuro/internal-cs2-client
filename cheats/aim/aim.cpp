#include "aim.h"
#include "../../sdk/interfaces/engineclient.h"
#include "../../sdk/bindings/playercontroller.h"
#include "../../sdk/bindings/playerpawn.h"
#include "../../src/cache/cache.h"
#include "../../src/cache/player.h"
#include "../../src/signatures/sig.h"
#include <Windows.h>

bool aim::EnableAimBot = false;
float aim::AimFOV = 5;

Vector aim::CalculateAngle(Vector localPos, Vector enemyPos, Vector viewAngles)
{
	return (enemyPos - localPos).ToAngle() - viewAngles;
}


void aim::AimBot()
{
    if (!CEngineClient::Get()->IsInGame() || !EnableAimBot || !GetAsyncKeyState(VK_MENU))
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

    const auto &localController = localplayer->Get();
    const auto &localPawn = localController->m_hPlayerPawn();

    auto bestFov = 150.f;
    auto bestAngle = Vector(0, 0, 0);

    float Yaw, Pitch;
	float Distance, Norm;
	Vector OppPos;

    Vector LocalPos = localPawn.Get()->m_vecViewOffset() + localPawn.Get()->m_pGameSceneNode()->m_vecOrigin();
    Vector viewAngle = *signatures::ViewAngles.GetPtrAs<Vector*>();

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
        if (!player)
        {
            continue;
        }

        if(!player->IsEnemyWithTeam(localplayer->GetTeam()))
        {
            continue;
        }

        CCSPlayerController *controller = player->Get();
        if (!controller || controller->m_bIsLocalPlayerController() || !controller->m_bPawnIsAlive())
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


        Vector HeadPos = boneArray[BONEINDEX::HEAD].Location;

		const auto CalcAngle = CalculateAngle(LocalPos, HeadPos, viewAngle + localPawn.Get()->m_aimPunchAngle());
        const auto fov = std::hypot(CalcAngle.x, CalcAngle.y);

        if (fov < bestFov)
        {
            bestFov = fov;
            bestAngle = CalcAngle;
        }
    }

    if(!bestAngle.isZero() && bestFov < AimFOV)
    {

        *signatures::ViewAngles.GetPtrAs<Vector*>() = viewAngle + bestAngle;
    }
}
