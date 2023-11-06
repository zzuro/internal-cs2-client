#include "player.h"
#include "cache.h"

#include "../../sdk/bindings/playercontroller.h"
#include "../../sdk/bindings/playerpawn.h"

#include "../../sdk/interfaces/engineclient.h"
#include "../../sdk/interfaces/cvar.h"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"
#include "../../cheats/vis/vis.h"


void CCachedPlayer::AntiFlash()
{
    
    CCSPlayerController* controller = Get();
    if (!controller || !controller->m_bPawnIsAlive()) {
        return;
    }

    C_CSPlayerPawnBase* pawn = controller->m_hPawn().Get();
    
    if(pawn->m_flFlashBangTime() > 0.0f){
        pawn->m_flFlashBangTime() = 0.0f;
    }
}

bool CCachedPlayer::CanDoESP() {
    CCSPlayerController* controller = Get();
    if (!controller || !controller->m_bPawnIsAlive()) {
        return false;
    }

    C_CSPlayerPawnBase* pawn = controller->m_hPawn().Get();
    if (!pawn || pawn->IsObserverPawn()) {
        return false;
    }

    return true;
}

void CCachedPlayer::DrawESP() {
    CCachedPlayer* cachedLocalPlayer = CMatchCache::GetLocalPlayer();
    if (!cachedLocalPlayer) {
        return InvalidateDrawInfo();
    }

    auto drawList = vis::drawList;

    const ImVec2& min = m_BBox.m_Mins;
    const ImVec2& max = m_BBox.m_Maxs;

    CCSPlayerController* controller = Get();
    C_CSPlayerPawnBase* pawn = controller->m_hPawn().Get();

     DrawBoundingBox([this, cachedLocalPlayer]() {
            if (IsLocalPlayer()) {
                return IM_COL32(52, 131, 235, 255);
            } else if (IsEnemyWithTeam(cachedLocalPlayer->GetTeam())) {
                return IM_COL32(255, 0, 0, 255);
            }

            return IM_COL32(0, 255, 0, 255);
    }());
 
}

void CCachedPlayer::CalculateDrawInfo() {
    CCSPlayerController* controller = Get();
    C_BaseEntity* pawn = controller->m_hPawn().Get();
    if (!pawn->CalculateBBoxByCollision(m_BBox)) {
        return InvalidateDrawInfo();
    }
}

CCachedPlayer::Team CCachedPlayer::GetTeam() {
    CCSPlayerController* controller = Get();
    if (!controller) return Team::UNKNOWN;

    C_CSPlayerPawnBase* pawn = controller->m_hPawn().Get();
    if (!pawn) return Team::UNKNOWN;

    return static_cast<Team>(pawn->m_iTeamNum());
}

bool CCachedPlayer::IsEnemyWithTeam(Team team) {
    static ConVar* mp_teammates_are_enemies = CCVar::Get()->GetCvarByName("mp_teammates_are_enemies");
    return mp_teammates_are_enemies->GetValue<bool>() ? true : GetTeam() != team;
}

bool CCachedPlayer::IsLocalPlayer() { return GetIndex() == CEngineClient::Get()->GetLocalPlayer(); }


