#include "mov.h"
#include "../../src/cache/cache.h"
#include "../../src/cache/player.h"
#include "../../sdk/interfaces/engineclient.h"
#include "../../sdk/bindings/playerpawn.h"
#include "../../sdk/bindings/playercontroller.h"
#include "../../src/signatures/sig.h"
#include <Windows.h>

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
    if (!controller || !controller->m_bPawnIsAlive())
    {
        return;
    }

    if (GetAsyncKeyState(VK_SPACE) < 0)
    {
        if (!(controller->m_fFlags() & 1))
        {
           *signatures::ForceJump.GetPtrAs<int*>() = 65537;
        }else
        {
            *signatures::ForceJump.GetPtrAs<int*>() = 256;
        }
    }
}
