#pragma once
#include "../../src/math/math.h"

namespace aim
{
    extern float AimFOV;
    
    extern bool EnableAimBot;
    void AimBot();

    Vector CalculateAngle(Vector localPos, Vector enemyPos, Vector viewAngles);
}