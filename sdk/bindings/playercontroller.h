#pragma once

#include "baseentity.h"

class C_CSPlayerPawnBase;

class CBasePlayerController : public C_BaseEntity {
   public:
    SCHEMA(CHandle<C_CSPlayerPawnBase>, m_hPawn, "CBasePlayerController", "m_hPawn");
    SCHEMA(bool, m_bIsLocalPlayerController , "CBasePlayerController", "m_bIsLocalPlayerController");
};

class CCSPlayerController : public CBasePlayerController {
   public:
    SCHEMA(bool, m_bPawnIsAlive, "CCSPlayerController", "m_bPawnIsAlive");
    SCHEMA(CHandle<C_CSPlayerPawnBase>, m_hPlayerPawn , "CCSPlayerController", "m_hPlayerPawn");
    SCHEMA(const char*, m_sSanitizedPlayerName, "CCSPlayerController", "m_sSanitizedPlayerName");
};