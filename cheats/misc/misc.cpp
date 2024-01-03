#include "misc.h"
#include "../../src/cache/cache.h"
#include "../../src/cache/player.h"
#include "../../sdk/interfaces/engineclient.h"
#include "../../sdk/bindings/playerpawn.h"
#include "../../sdk/bindings/playercontroller.h"
#include "../../src/signatures/sig.h"
#include <Windows.h>
#include <iostream>
#include <thread>

bool misc::EnableBhop = false;
void misc::Bhop(CUserCmd *cmd)
{

    static int32_t last_tick = 0;
    static bool jumped = true;
    
    if (!CEngineClient::Get()->IsInGame() || !misc::EnableBhop)
    {
        return;
    }

    const auto &localplayer = CMatchCache::GetLocalPlayer();
    if (!localplayer)
    {
        return;
    }

    if (!localplayer->CanDoESP())
    {
        return;
    }

    CCSPlayerController *controller = localplayer->Get();
    C_CSPlayerPawnBase *pawn = controller->m_hPlayerPawn().Get();

    //printf("ticks: %d\n", cmd->cmd.base->tick_count);
    if(jumped && pawn->m_fFlags() & (1 << 0))
    {
        last_tick = cmd->cmd.base->tick_count;
        jumped = false;
    }

    if(last_tick + 20> cmd->cmd.base->tick_count && !jumped)
    {
        cmd->button_states.buttonstate1 &= ~IN_JUMP;
        std::cout << "cancel jump" << std::endl;
        return;
    }

    if (GetAsyncKeyState(VK_SPACE) && !(pawn->m_fFlags() & (1 << 0)))
    {
        jumped = true;
        cmd->button_states.buttonstate1 &= ~IN_JUMP;
    }
   
}
