#pragma once

#include "baseentity.h"

class C_CSPlayerPawnBase : public C_BaseEntity {
   public:
    bool IsPlayerPawn();
    bool IsObserverPawn();

    SCHEMA(float, m_flFlashBangTime, "C_CSPlayerPawnBase", "m_flFlashBangTime");
    SCHEMA(uint32_t, m_fFlags, "C_BaseEntity", "m_fFlags");

    //SHOTSFIRED
    //AimPunchCache
    //PunchAngle
    //enemyPos
    //localPos
    //viewAngles
    //cameraPos
    //
};