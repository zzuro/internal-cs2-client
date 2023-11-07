#pragma once

#include "baseentity.h"

class C_CSPlayerPawnBase : public C_BaseEntity {
   public:
    bool IsPlayerPawn();
    bool IsObserverPawn();

    SCHEMA(float, m_flFlashBangTime, "C_CSPlayerPawnBase", "m_flFlashBangTime");
    //SHOTSFIRED
    //AimPunchCache
    //PunchAngle
    //enemyPos
    //localPos
    //viewAngles
    //cameraPos
    //
};