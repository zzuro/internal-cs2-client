#define IMGUI_DEFINE_MATH_OPERATORS
#include "gui.h"
#include "../../cheats/vis/vis.h"
#include "../hook/hook.h"
#include "../../sdk/interfaces/inputsystem.h"
#include "../../sdk/sdl/sdl.h"



void gui::shotdown()
{
    hook::open = false;
    auto inputSystem = CInputSystem::Get();
    if (inputSystem && inputSystem->IsRelativeMouseMode())
    {
        const ImVec2 screenCenter = ImGui::GetIO().DisplaySize / 2.f;
        sdl::SetRelativeMouseMode(!hook::open);
        sdl::SetWindowGrab(inputSystem->GetSDLWindow(), !hook::open);
        sdl::WarpMouseInWindow(nullptr, screenCenter.x, screenCenter.y);
    }
}

void gui::render()
{   
    if (GetAsyncKeyState(VK_INSERT) & 1)
    {
        if (!ImGui::GetCurrentContext())
        {
            return;
        }

        hook::open = !hook::open;

        auto inputSystem = CInputSystem::Get();
        if (inputSystem && inputSystem->IsRelativeMouseMode())
        {
            const ImVec2 screenCenter = ImGui::GetIO().DisplaySize / 2.f;
            sdl::SetRelativeMouseMode(!hook::open);
            sdl::SetWindowGrab(inputSystem->GetSDLWindow(), !hook::open);
            sdl::WarpMouseInWindow(nullptr, screenCenter.x, screenCenter.y);
        }
    }

    renderGUI();
}

void gui::renderGUI(){

    
    ImGuiIO& IO = ImGui::GetIO();
    IO.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

    if (!hook::open) {
        return;
    }

    IO.ConfigFlags = ImGuiConfigFlags_None;
    
    auto inputSystem = CInputSystem::Get();
    if (inputSystem) {
        sdl::SetRelativeMouseMode(false);
        sdl::SetWindowGrab(inputSystem->GetSDLWindow(), false);
    }

    ImGui::SetNextWindowPos(IO.DisplaySize / 2.f, ImGuiCond_Once, {0.5f, 0.5f});
	ImGui::SetWindowSize({800, 600});
	ImGui::Begin("Menu", &hook::open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::Checkbox("BoxESP", &vis::DrawBoxESP);
    ImGui::Checkbox("WeaponESP", &vis::WeaponESP);
    ImGui::Checkbox("NoFlash", &vis::EnableNoFlash);
	ImGui::End();
}