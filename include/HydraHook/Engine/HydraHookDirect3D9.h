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


#ifndef HydraHookDirect3D9_h__
#define HydraHookDirect3D9_h__

#ifndef HYDRAHOOK_NO_D3D9

#include "HydraHookCore.h"
#include <d3d9.h>

typedef
_Function_class_(EVT_HYDRAHOOK_D3D9_PRESENT)
VOID
EVT_HYDRAHOOK_D3D9_PRESENT(
    LPDIRECT3DDEVICE9   pDevice,
    const RECT          *pSourceRect,
    const RECT          *pDestRect,
    HWND                hDestWindowOverride,
    const RGNDATA       *pDirtyRegion
);

typedef EVT_HYDRAHOOK_D3D9_PRESENT *PFN_HYDRAHOOK_D3D9_PRESENT;

typedef
_Function_class_(EVT_HYDRAHOOK_D3D9_RESET)
VOID
EVT_HYDRAHOOK_D3D9_RESET(
    LPDIRECT3DDEVICE9       pDevice,
    D3DPRESENT_PARAMETERS   *pPresentationParameters
);

typedef EVT_HYDRAHOOK_D3D9_RESET *PFN_HYDRAHOOK_D3D9_RESET;

typedef
_Function_class_(EVT_HYDRAHOOK_D3D9_END_SCENE)
VOID
EVT_HYDRAHOOK_D3D9_END_SCENE(
    LPDIRECT3DDEVICE9 pDevice
);

typedef EVT_HYDRAHOOK_D3D9_END_SCENE *PFN_HYDRAHOOK_D3D9_END_SCENE;

typedef
_Function_class_(EVT_HYDRAHOOK_D3D9_PRESENT_EX)
VOID
EVT_HYDRAHOOK_D3D9_PRESENT_EX(
    LPDIRECT3DDEVICE9EX     pDevice,
    const RECT              *pSourceRect,
    const RECT              *pDestRect,
    HWND                    hDestWindowOverride,
    const RGNDATA           *pDirtyRegion,
    DWORD                   dwFlags
);

typedef EVT_HYDRAHOOK_D3D9_PRESENT_EX *PFN_HYDRAHOOK_D3D9_PRESENT_EX;

typedef
_Function_class_(EVT_HYDRAHOOK_D3D9_RESET_EX)
VOID
EVT_HYDRAHOOK_D3D9_RESET_EX(
    LPDIRECT3DDEVICE9EX     pDevice,
    D3DPRESENT_PARAMETERS   *pPresentationParameters,
    D3DDISPLAYMODEEX        *pFullscreenDisplayMode
);

typedef EVT_HYDRAHOOK_D3D9_RESET_EX *PFN_HYDRAHOOK_D3D9_RESET_EX;


typedef struct _HYDRAHOOK_D3D9_EVENT_CALLBACKS
{
    PFN_HYDRAHOOK_D3D9_PRESENT       EvtHydraHookD3D9PrePresent;
    PFN_HYDRAHOOK_D3D9_PRESENT       EvtHydraHookD3D9PostPresent;

    PFN_HYDRAHOOK_D3D9_RESET         EvtHydraHookD3D9PreReset;
    PFN_HYDRAHOOK_D3D9_RESET         EvtHydraHookD3D9PostReset;

    PFN_HYDRAHOOK_D3D9_END_SCENE     EvtHydraHookD3D9PreEndScene;
    PFN_HYDRAHOOK_D3D9_END_SCENE     EvtHydraHookD3D9PostEndScene;

    PFN_HYDRAHOOK_D3D9_PRESENT_EX    EvtHydraHookD3D9PrePresentEx;
    PFN_HYDRAHOOK_D3D9_PRESENT_EX    EvtHydraHookD3D9PostPresentEx;

    PFN_HYDRAHOOK_D3D9_RESET_EX      EvtHydraHookD3D9PreResetEx;
    PFN_HYDRAHOOK_D3D9_RESET_EX      EvtHydraHookD3D9PostResetEx;

} HYDRAHOOK_D3D9_EVENT_CALLBACKS, *PHYDRAHOOK_D3D9_EVENT_CALLBACKS;

/**
 * \fn  VOID FORCEINLINE HYDRAHOOK_D3D9_EVENT_CALLBACKS_INIT( _Out_ PHYDRAHOOK_D3D9_EVENT_CALLBACKS Callbacks )
 *
 * \brief   The Direct3D 9(Ex) event callback collection to initialize.
 *
 * \author  Benjamin Höglinger-Stelzer
 * \date    06.05.2019
 *
 * \param   Callbacks   The callback collection.
 *
 * \returns Nothing.
 */
VOID FORCEINLINE HYDRAHOOK_D3D9_EVENT_CALLBACKS_INIT(
    _Out_ PHYDRAHOOK_D3D9_EVENT_CALLBACKS Callbacks
)
{
    ZeroMemory(Callbacks, sizeof(HYDRAHOOK_D3D9_EVENT_CALLBACKS));
}

#ifdef __cplusplus
extern "C" {
#endif

    HYDRAHOOK_API PHYDRAHOOK_ENGINE HydraHookEngineGetHandleFromD3D9Device(
        _In_
        LPDIRECT3DDEVICE9 Device
    );

    HYDRAHOOK_API PHYDRAHOOK_ENGINE HydraHookEngineGetHandleFromD3D9ExDevice(
        _In_
        LPDIRECT3DDEVICE9EX Device
    );

#ifdef __cplusplus
}
#endif

#endif

#endif // HydraHookDirect3D9_h__
