#include "hook.h"
#include "../math/math.h"
#include "../cache/cache.h"
#include "../../kiero/minhook/include/MinHook.h"
#include <stdexcept>
#include "../signatures/sig.h"
#include "../../sdk/interfaces/gameentitysystem.h"
#include "../../sdk/interfaces/source2client.h"
#include "../cache/cache.h"
#include <iostream>
#include "../../cheats/vis/vis.h"
#include "../../cheats/misc/misc.h"
#include "../gui/gui.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present hook::oPresent;
HWND hook::window = NULL;
WNDPROC hook::oWndProc;
ID3D11Device *hook::pDevice = NULL;
ID3D11DeviceContext *hook::pContext = NULL;
ID3D11RenderTargetView *hook::mainRenderTargetView;
bool hook::open = false;

void hook::InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall hook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	if (open)
	{
		// Messages handled by 'ImGui_ImplWin32_WndProcHandler'.
		switch (uMsg)
		{
		case WM_MOUSEMOVE:
		case WM_NCMOUSEMOVE:
		case WM_MOUSELEAVE:
		case WM_NCMOUSELEAVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONDBLCLK:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_MOUSEHWHEEL:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_SETFOCUS:
		case WM_KILLFOCUS:
		case WM_CHAR:
		case WM_SETCURSOR:
		case WM_DEVICECHANGE:
			return 1;
		}
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool hook::init = false;
HRESULT __stdcall hook::hkPresent(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D *pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	vis::drawList = ImGui::GetBackgroundDrawList();
	gui::watermark();
	gui::render();
	vis::BoxESP();
	vis::NoFlash();
	vis::SkeletonESP();
	vis::DrawFOV();
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	

	return oPresent(pSwapChain, SyncInterval, Flags);
}

bool hook::VirtualFunction(CPointer ptr, size_t index, const char *name, void *fn, void **orig)
{
	void *rt = vt::GetMethod(ptr, index).Get<void *>();
	std::cout << "[hook]: " << name << " -> " << std::hex << rt << std::endl;
	if (MH_CreateHook(rt, fn, orig))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool hook::Function(CPointer ptr, const char* name, void *fn, void **orig)
{
	void *rt = ptr.Get<void *>();
	std::cout << "[hook]: " << name << " -> " << std::hex << rt << std::endl;
	if(MH_CreateHook(rt, fn, orig))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void hook::Init()
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void **)&hook::oPresent, hook::hkPresent);
			init_hook = true;
		}
	} while (!init_hook);

	CMatchCache::Initialize();
	if (hook::VirtualFunction(signatures::GetCSGOInput.GetPtrAs<void *>(), 12, "MouseInputEnabled", &hkMouseInputEnabled, (void **)&oMouseInputEnabled))
	{
		throw std::runtime_error("Failed to create hook for MouseInputEnabled");
	}

	if (hook::VirtualFunction(CGameEntitySystem::Get(), 14, "OnAddEntity", &hkOnAddEntity, (void **)&oOnAddEntity))
	{
		throw std::runtime_error("Failed to create hook for OnAddEntity");
	}
	
	if (hook::VirtualFunction(CGameEntitySystem::Get(), 15, "OnRemoveEntity", &hkOnRemoveEntity, (void **)&oOnRemoveEntity))
	{
		throw std::runtime_error("Failed to create hook for OnRemoveEntity");
	}
	
	if(hook::Function(signatures::GetMatricesForView.GetPtrAs<void *>(), "GetMatricesForView", &hkGetMatricesForView, (void **)&oGetMatricesForView))
	{
		throw std::runtime_error("Failed to create hook for GetMatricesForView");
	}
	
	
	if (MH_EnableHook(MH_ALL_HOOKS))
	{
		throw std::runtime_error("Unable to enable hooks");
	}

	
}

void hook::Shutdown()
{
	gui::shotdown();
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
	kiero::shutdown();
}

void *hook::oMouseInputEnabled = nullptr;
bool hook::hkMouseInputEnabled(void *rcx)
{

	if (open)
	{
		return false;
	}
	else
	{
		return CallOriginal<bool>(oMouseInputEnabled, rcx);
	}
}

void *hook::oOnAddEntity = nullptr;
void *hook::hkOnAddEntity(void *rcx, CEntityInstance *inst, CBaseHandle handle)
{
	CMatchCache::AddEntity(inst, handle);
	return CallOriginal<void *>(oOnAddEntity, rcx, inst, handle);
}

void *hook::oOnRemoveEntity = nullptr;
void *hook::hkOnRemoveEntity(void *rcx, CEntityInstance *inst, CBaseHandle handle)
{
	CMatchCache::RemoveEntity(inst, handle);
	return CallOriginal<void *>(oOnRemoveEntity, rcx, inst, handle);
}

void *hook::oGetMatricesForView = nullptr;
void hook::hkGetMatricesForView(void *rcx, void *view, VMatrix *pWorldToView, VMatrix *pViewToProjection, VMatrix *pWorldToProjection, VMatrix *pWorldToPixels)
{
	CallOriginal<void>(oGetMatricesForView, rcx, view, pWorldToView, pViewToProjection, pWorldToProjection, pWorldToPixels);
	CMath::Get().UpdateViewMatrix(pWorldToProjection);
	vis::UpdateESP();
}

