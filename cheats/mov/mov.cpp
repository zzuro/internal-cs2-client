#include "mov.h"
#include "../../src/cache/cache.h"
#include "../../src/cache/player.h"
#include "../../sdk/interfaces/engineclient.h"
#include "../../sdk/bindings/playerpawn.h"
#include "../../sdk/bindings/playercontroller.h"
#include "../../src/signatures/sig.h"
#include <Windows.h>
#include <iostream>
#include <thread>

#define IN_JUMP 0x2
#define FL_ONGROUND 0x1

bool mov::EnableBhop = false;

void mov::Bhop()
{
    if (!CEngineClient::Get()->IsInGame() || !mov::EnableBhop)
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

    if ((GetAsyncKeyState(VK_SPACE) < 0) && *signatures::ForceJump.GetPtrAs<ULONG64 *>() == 256)
    {
        *signatures::ForceJump.GetPtrAs<ULONG64*>() = 65537;
    }else
    {
        *signatures::ForceJump.GetPtrAs<ULONG64 *>() = 256;
    }
    
}
