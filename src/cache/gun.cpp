#include "gun.h"

#include "../../sdk/bindings/baseentity.h"
#include "../../cheats/vis/vis.h"

bool CCachedGun::CanDoESP() {
    C_BaseEntity* weapon = Get();
    if (!weapon || weapon->m_hOwnerEntity().IsValid()) {
        return false;
    }

    return true;
}

void CCachedGun::DrawESP() {
    if (vis::WeaponESP) {
        DrawBoundingBox(IM_COL32(255, 255, 0, 255));
    }
}