#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "../../kiero/kiero.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "../../sdk/bindings/baseentity.h"
#include "../math/types/vmatrix.h"

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

    void Init();
    void Shutdown();

    void InitImGui();

    template <typename T, typename... Args>
    auto CallOriginal(void* m_Original, Args... args) {
        return CPointer(m_Original).Call<T (*)(Args...)>(std::forward<Args>(args)...);
    }


    LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

    
    extern void* oOnAddEntity;
    void* hkOnAddEntity(void* rcx, CEntityInstance* inst, CBaseHandle handle);
    bool hkMouseInputEnabled(void* rcx);
    void hkGetMatricesForView(void* rcx, void* view, VMatrix* pWorldToView, VMatrix* pViewToProjection, VMatrix* pWorldToProjection, VMatrix* pWorldToPixels);

   
}


