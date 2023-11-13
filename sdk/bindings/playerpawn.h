#pragma once

#include "baseentity.h"

class C_CSPlayerPawnBase : public C_BaseEntity {
   public:
    bool IsPlayerPawn();
    bool IsObserverPawn();

    SCHEMA(float, m_flFlashBangTime, "C_CSPlayerPawnBase", "m_flFlashBangTime");
    SCHEMA(uint32_t, m_fFlags, "C_BaseEntity", "m_fFlags");
    SCHEMA(Vector, m_vecLastClipCameraPos, "C_CSPlayerPawnBase", "m_vecLastClipCameraPos");
    SCHEMA(Vector, m_aimPunchAngle, "C_CSPlayerPawn", "m_aimPunchAngle");
    
};