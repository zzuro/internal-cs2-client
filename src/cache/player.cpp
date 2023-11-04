
#include "player.h"
#include "cache.h"


#include "../../sdk/bindings/playercontroller.h"
#include "../../sdk/bindings/playerpawn.h"

#include "../../sdk/interfaces/engineclient.h"
#include "../../sdk/interfaces/cvar.h"

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