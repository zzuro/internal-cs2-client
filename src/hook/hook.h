#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "../../kiero/kiero.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx11.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

namespace hook{
    extern Present oPresent;
    extern HWND window;
    extern WNDPROC oWndProc;
    extern ID3D11Device* pDevice;
    extern ID3D11DeviceContext* pContext;
    extern ID3D11RenderTargetView* mainRenderTargetView;

    extern bool init;
    extern bool open;

    void InitImGui();
    LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

    void Init();
    void Shutdown();

}


