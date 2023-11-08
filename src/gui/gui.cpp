#define IMGUI_DEFINE_MATH_OPERATORS
#include "gui.h"
#include "../../cheats/vis/vis.h"
#include "../hook/hook.h"
#include "../../sdk/interfaces/inputsystem.h"
#include "../../sdk/sdl/sdl.h"
#include "../../sdk/interfaces/engineclient.h"
#include <ctime>
#include <iomanip>
#include <sstream>

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
    ImGui::Checkbox("SkeletonESP", &vis::EnableSkeletonESP);
	ImGui::End();
}


void gui::watermark()
{
    auto drawList = vis::drawList;
    char framerate[128];

    time_t rawtime;
    struct tm * timeinfo;

    char time_[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    std::time_t currentTime = std::time(nullptr);
    std::tm *timeInfo = std::localtime(&currentTime);

    std::ostringstream oss;
    oss << std::put_time(timeInfo, "%d %b %Y");

    std::string str_date = oss.str();
    strftime(time_,sizeof(time_),"%H:%M:%S",timeinfo);
    std::string str_time(time_);

    snprintf(framerate, IM_ARRAYSIZE(framerate), "CS2 Client [%d]\nFPS: %d\n\n%s %s\n",
             CEngineClient::Get()->GetEngineBuildNumber(), static_cast<int>(ImGui::GetIO().Framerate), str_date.c_str(), str_time.c_str());

    drawList->AddText({17, 9}, IM_COL32(0, 0, 0, 255), framerate);
    drawList->AddText({16, 8}, IM_COL32(27, 227, 200, 255), framerate);

}