/*
MIT License

Copyright (c) 2018-2026 Benjamin HÃ¶glinger-Stelzer

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


#ifndef HydraHookDirect3D12_h__
#define HydraHookDirect3D12_h__

#ifndef HYDRAHOOK_NO_D3D12

#include <dxgi.h>

typedef
_Function_class_(EVT_HYDRAHOOK_D3D12_PRESENT)
VOID
EVT_HYDRAHOOK_D3D12_PRESENT(
    IDXGISwapChain  *pSwapChain,
    UINT            SyncInterval,
    UINT            Flags
);

typedef EVT_HYDRAHOOK_D3D12_PRESENT *PFN_HYDRAHOOK_D3D12_PRESENT;

typedef
_Function_class_(EVT_HYDRAHOOK_D3D12_RESIZE_TARGET)
VOID
EVT_HYDRAHOOK_D3D12_RESIZE_TARGET(
    IDXGISwapChain          *pSwapChain,
    const DXGI_MODE_DESC    *pNewTargetParameters
);

typedef EVT_HYDRAHOOK_D3D12_RESIZE_TARGET *PFN_HYDRAHOOK_D3D12_RESIZE_TARGET;

typedef
_Function_class_(EVT_HYDRAHOOK_D3D12_RESIZE_BUFFERS)
VOID
EVT_HYDRAHOOK_D3D12_RESIZE_BUFFERS(
    IDXGISwapChain  *pSwapChain,
    UINT            BufferCount,
    UINT            Width,
    UINT            Height,
    DXGI_FORMAT     NewFormat,
    UINT            SwapChainFlags
);

typedef EVT_HYDRAHOOK_D3D12_RESIZE_BUFFERS *PFN_HYDRAHOOK_D3D12_RESIZE_BUFFERS;


typedef struct _HYDRAHOOK_D3D12_EVENT_CALLBACKS
{
    PFN_HYDRAHOOK_D3D12_PRESENT          EvtHydraHookD3D12PrePresent;
    PFN_HYDRAHOOK_D3D12_PRESENT          EvtHydraHookD3D12PostPresent;

    PFN_HYDRAHOOK_D3D12_RESIZE_TARGET    EvtHydraHookD3D12PreResizeTarget;
    PFN_HYDRAHOOK_D3D12_RESIZE_TARGET    EvtHydraHookD3D12PostResizeTarget;

    PFN_HYDRAHOOK_D3D12_RESIZE_BUFFERS   EvtHydraHookD3D12PreResizeBuffers;
    PFN_HYDRAHOOK_D3D12_RESIZE_BUFFERS   EvtHydraHookD3D12PostResizeBuffers;

} HYDRAHOOK_D3D12_EVENT_CALLBACKS, *PHYDRAHOOK_D3D12_EVENT_CALLBACKS;

/**
 * \fn  VOID FORCEINLINE HYDRAHOOK_D3D12_EVENT_CALLBACKS_INIT( _Out_ PHYDRAHOOK_D3D12_EVENT_CALLBACKS Callbacks )
 *
 * \brief   The Direct3D 12 event callback collection to initialize.
 *
 * \author  Benjamin HÃ¶glinger-Stelzer
 * \date    06.05.2019
 *
 * \param   Callbacks   The callback collection.
 *
 * \returns Nothing.
 */
VOID FORCEINLINE HYDRAHOOK_D3D12_EVENT_CALLBACKS_INIT(
    _Out_ PHYDRAHOOK_D3D12_EVENT_CALLBACKS Callbacks
)
{
    ZeroMemory(Callbacks, sizeof(HYDRAHOOK_D3D12_EVENT_CALLBACKS));
}

#endif

#endif // HydraHookDirect3D12_h__
