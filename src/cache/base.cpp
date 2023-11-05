#define IMGUI_DEFINE_MATH_OPERATORS
#include "base.h"
#include "../../sdk/bindings/baseentity.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"

bool CCachedBaseEntity::CanDoESP() { return Get() != nullptr; }
void CCachedBaseEntity::InvalidateDrawInfo() { m_BBox.Invalidate(); }

void CCachedBaseEntity::DrawESP() {
    DrawBoundingBox(IM_COL32(255, 255, 255, 255));
}

void CCachedBaseEntity::DrawBoundingBox(ImU32 color) {
    static constexpr auto outlineColor = IM_COL32(0, 0, 0, 255);

    auto drawList = ImGui::GetBackgroundDrawList();

    const ImVec2& min = m_BBox.m_Mins;
    const ImVec2& max = m_BBox.m_Maxs;
    drawList->AddRect(min - ImVec2{1.f, 1.f}, max + ImVec2{1.f, 1.f}, outlineColor);
    drawList->AddRect(min + ImVec2{1.f, 1.f}, max - ImVec2{1.f, 1.f}, outlineColor);
    drawList->AddRect(min, max, color);
    
}

void CCachedBaseEntity::CalculateDrawInfo() {
    C_BaseEntity* ent = Get();

    if (!ent->CalculateBBoxByHitbox(m_BBox)) {
        return InvalidateDrawInfo();
    }
}
