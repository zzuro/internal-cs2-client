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
void misc::Bhop(CUserCmd* cmd)
{

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
    
    if (GetAsyncKeyState(VK_SPACE) && *signatures::ForceJump.GetPtrAs<ULONG64 *>() == 256)
    {
        *signatures::ForceJump.GetPtrAs<ULONG64*>() = 65537;
    }else{
        *signatures::ForceJump.GetPtrAs<ULONG64 *>() = 256;
    }
    
} 
