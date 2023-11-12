#pragma once
#include "../../imgui/imgui.h"


namespace vis
{
    extern ImDrawList* drawList;
    
    extern bool DrawBoxESP;
    extern bool WeaponESP;
    extern bool EnableNoFlash;
    extern bool EnableSkeletonESP;
    extern bool EnableNames;
    extern bool EnableHealth;

    void BoxESP();
    void UpdateESP();
    void NoFlash();
    void SkeletonESP();
}