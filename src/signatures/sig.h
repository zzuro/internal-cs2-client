#pragma once

#include "../sigscan/sigscan.h"

namespace signatures {
    extern CSigScan GetBaseEntity, GetHighestEntityIndex;
    extern CSigScan GetCSGOInput;
    extern CSigScan GetMatricesForView;
    extern CSigScan GetHitboxSet;
    extern CSigScan HitboxToWorldTransforms;
    extern CSigScan ForceJump;
}  