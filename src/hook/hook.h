#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "../../kiero/kiero.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "../../sdk/bindings/baseentity.h"
#include "../../sdk/interfaces/inputsystem.h"
#include "../math/types/vmatrix.h"
#include "../virtual/virtual.h"
#include <iostream>

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

    bool VirtualFunction(CPointer ptr, size_t index, const char *name, void *fn, void **orig);
    bool Function(CPointer ptr, const char* name, void *fn, void **orig);
	

    LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

    
    extern void* oOnAddEntity;
    void* hkOnAddEntity(void* rcx, CEntityInstance* inst, CBaseHandle handle);

    extern void* oOnRemoveEntity;
    void* hkOnRemoveEntity(void* rcx, CEntityInstance* inst, CBaseHandle handle);

    extern void* oMouseInputEnabled;
    bool hkMouseInputEnabled(void* rcx);

    extern void* oGetMatricesForView;
    void hkGetMatricesForView(void* rcx, void* view, VMatrix* pWorldToView, VMatrix* pViewToProjection, VMatrix* pWorldToProjection, VMatrix* pWorldToPixels);

    extern void* oCreateMove;
    bool hkCreateMove(CInputSystem* input, std::uint32_t a2, std::uint8_t a3);

}


