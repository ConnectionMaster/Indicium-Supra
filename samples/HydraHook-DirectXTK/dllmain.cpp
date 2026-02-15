/*
MIT License

Copyright (c) 2018 Benjamin Höglinger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <HydraHook/Engine/HydraHookDirect3D11.h>
#include <HydraHook/Engine/HydraHookCore.h>
#include <cassert>
#include <string>

#include <directxtk/SpriteBatch.h>
#include <directxtk/SpriteFont.h>
#include <directxtk/CommonStates.h>

using namespace DirectX;

static HMODULE g_hModule = nullptr;

typedef struct _DX11_TEXT_CTX
{
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* ctx = nullptr;
	std::unique_ptr<SpriteBatch> spriteBatch;
	std::unique_ptr<SpriteFont> spriteFont;
	std::unique_ptr<CommonStates> commonStates;
} DX11_TEXT_CTX, *PDX11_TEXT_CTX;

EVT_HYDRAHOOK_GAME_HOOKED EvtHydraHookGameHooked;
EVT_HYDRAHOOK_D3D11_PRE_PRESENT EvtHydraHookD3D11PrePresent;
EVT_HYDRAHOOK_GAME_UNHOOKED EvtHydraHookGamePostUnhooked;

static std::wstring GetFontPath()
{
	wchar_t path[MAX_PATH];
	if (GetModuleFileNameW(g_hModule, path, MAX_PATH) == 0)
		return L"";

	std::wstring fontPath(path);
	const size_t lastSlash = fontPath.find_last_of(L"\\/");
	if (lastSlash != std::wstring::npos)
		fontPath = fontPath.substr(0, lastSlash + 1);
	fontPath += L"Arial.spritefont";
	return fontPath;
}

/**
 * \fn	BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
 *
 * \brief	Your typical DLL entry point function. We're not doing much here since a special
 * 			initialization routine gets called upon getting loaded by HydraHook.
 *
 * \author	Benjamin "Nefarius" Höglinger
 * \date	05.05.2018
 *
 * \param	hInstance 	The instance.
 * \param	dwReason  	The reason.
 * \param	parameter3	The third parameter.
 *
 * \returns	A WINAPI.
 */
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
	//
	// We don't need to get notified in thread attach- or detachments
	// 
	DisableThreadLibraryCalls(static_cast<HMODULE>(hInstance));

	g_hModule = static_cast<HMODULE>(hInstance);

	HYDRAHOOK_ENGINE_CONFIG cfg;
	HYDRAHOOK_ENGINE_CONFIG_INIT(&cfg);

	// Only attempt to detect and hook D3D11
	cfg.Direct3D.HookDirect3D11 = TRUE;
	// Called once game as been hooked
	cfg.EvtHydraHookGameHooked = EvtHydraHookGameHooked;
	// Called after hooks have been removed
	cfg.EvtHydraHookGamePostUnhook = EvtHydraHookGamePostUnhooked;

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:

		//
		// Bootstrap the engine. Allocates resources, establishes hooks etc.
		// 
		(void)HydraHookEngineCreate(
			static_cast<HMODULE>(hInstance),
			&cfg,
			NULL
		);

		break;
	case DLL_PROCESS_DETACH:

		//
		// Tears down the engine. Graceful shutdown, frees resources etc.
		// 
		(void)HydraHookEngineDestroy(static_cast<HMODULE>(hInstance));
		g_hModule = nullptr;

		break;
	default:
		break;
	}

	return TRUE;
}

//
// Essential game functions successfully hooked, do further bootstrapping here
// 
void EvtHydraHookGameHooked(
	PHYDRAHOOK_ENGINE EngineHandle,
	const HYDRAHOOK_D3D_VERSION GameVersion
)
{
	//
	// At this stage we assume D3D11
	// 
	assert(GameVersion == HydraHookDirect3DVersion11);

	PDX11_TEXT_CTX pCtx = nullptr;

	//
	// Allocate context memory
	// 
	assert(HydraHookEngineAllocCustomContext(
		EngineHandle,
		(PVOID*)&pCtx,
		sizeof(DX11_TEXT_CTX)
	) == HYDRAHOOK_ERROR_NONE);

	// Placement new to construct the struct (it has non-trivial members)
	new (pCtx) DX11_TEXT_CTX();

	HYDRAHOOK_D3D11_EVENT_CALLBACKS d3d11;
	HYDRAHOOK_D3D11_EVENT_CALLBACKS_INIT(&d3d11);
	d3d11.EvtHydraHookD3D11PrePresent = EvtHydraHookD3D11PrePresent;

	// Begin invoking render hook callbacks
	HydraHookEngineSetD3D11EventCallbacks(EngineHandle, &d3d11);
}

//
// Game unloading, hooks are removed
// 
void EvtHydraHookGamePostUnhooked(PHYDRAHOOK_ENGINE EngineHandle)
{
	PDX11_TEXT_CTX pCtx = PDX11_TEXT_CTX(HydraHookEngineGetCustomContext(EngineHandle));
	if (pCtx)
		pCtx->~DX11_TEXT_CTX();
}

//
// Present is about to get called
// 
void EvtHydraHookD3D11PrePresent(
	IDXGISwapChain					*pSwapChain,
	UINT							SyncInterval,
	UINT							Flags,
	PHYDRAHOOK_EVT_PRE_EXTENSION     Extension
)
{
	const PDX11_TEXT_CTX pCtx = PDX11_TEXT_CTX(Extension->Context);
	ID3D11Device* pDeviceTmp = nullptr;

	if (FAILED(D3D11_DEVICE_FROM_SWAPCHAIN(pSwapChain, &pDeviceTmp)))
	{
		HydraHookEngineLogError("Failed to get device pointer from swapchain");
		return;
	}

	/*
	 * Swapchain associated Device and Context pointers can become invalid
	 * when the host process destroys and re-creates them (like RetroArch
	 * does when switching cores) so compare to ones grabbed earlier and
	 * re-request both if necessary.
	 */
	if (pCtx->dev != pDeviceTmp)
	{
		pCtx->spriteBatch.reset();
		pCtx->spriteFont.reset();
		pCtx->commonStates.reset();

		D3D11_DEVICE_IMMEDIATE_CONTEXT_FROM_SWAPCHAIN(
			pSwapChain,
			&pCtx->dev,
			&pCtx->ctx
		);

		const std::wstring fontPath = GetFontPath();
		if (fontPath.empty() || GetFileAttributesW(fontPath.c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			HydraHookEngineLogError("Arial.spritefont not found next to DLL. Run MakeSpriteFont on arial.ttf and place output alongside the DLL.");
			return;
		}

		try
		{
			pCtx->commonStates = std::make_unique<CommonStates>(pCtx->dev);
			pCtx->spriteBatch = std::make_unique<SpriteBatch>(pCtx->ctx);
			pCtx->spriteFont = std::make_unique<SpriteFont>(pCtx->dev, fontPath.c_str());
		}
		catch (const std::exception& e)
		{
			HydraHookEngineLogError("Failed to create DirectXTK resources: %s", e.what());
			return;
		}
	}

	ID3D11Texture2D* pBackBuffer = nullptr;
	if (FAILED(D3D11_BACKBUFFER_FROM_SWAPCHAIN(pSwapChain, &pBackBuffer)))
	{
		HydraHookEngineLogError("Failed to get back buffer from swapchain");
		return;
	}

	ID3D11RenderTargetView* pRTV = nullptr;
	HRESULT hr = pCtx->dev->CreateRenderTargetView(pBackBuffer, nullptr, &pRTV);
	pBackBuffer->Release();

	if (FAILED(hr) || !pRTV)
	{
		HydraHookEngineLogError("Failed to create render target view");
		return;
	}

	pCtx->ctx->OMSetRenderTargets(1, &pRTV, nullptr);

	pCtx->spriteBatch->Begin(SpriteSortMode_Deferred, pCtx->commonStates->AlphaBlend());
	pCtx->spriteFont->DrawString(
		pCtx->spriteBatch.get(),
		L"Injected via HydraHook by Nefarius",
		XMFLOAT2(15.0f, 30.0f),
		Colors::White,
		0.0f,
		XMFLOAT2(0, 0),
		1.0f
	);
	pCtx->spriteBatch->End();

	pRTV->Release();
}
