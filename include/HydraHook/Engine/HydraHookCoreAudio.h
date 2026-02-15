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


#ifndef HydraHookCoreAudio_h__
#define HydraHookCoreAudio_h__

#include "HydraHookCore.h"
#include <Audioclient.h>

typedef
_Function_class_(EVT_HYDRAHOOK_ARC_PRE_GET_BUFFER)
VOID
EVT_HYDRAHOOK_ARC_PRE_GET_BUFFER(
    IAudioRenderClient*             client,
    UINT32                          NumFramesRequested,
    BYTE                            **ppData,
    PHYDRAHOOK_EVT_PRE_EXTENSION     Extension
);

typedef EVT_HYDRAHOOK_ARC_PRE_GET_BUFFER *PFN_HYDRAHOOK_ARC_PRE_GET_BUFFER;

typedef
_Function_class_(EVT_HYDRAHOOK_ARC_POST_GET_BUFFER)
VOID
EVT_HYDRAHOOK_ARC_POST_GET_BUFFER(
    IAudioRenderClient*             client,
    UINT32                          NumFramesRequested,
    BYTE                            **ppData,
    PHYDRAHOOK_EVT_POST_EXTENSION    Extension
);

typedef EVT_HYDRAHOOK_ARC_POST_GET_BUFFER *PFN_HYDRAHOOK_ARC_POST_GET_BUFFER;

typedef
_Function_class_(EVT_HYDRAHOOK_ARC_PRE_RELEASE_BUFFER)
VOID
EVT_HYDRAHOOK_ARC_PRE_RELEASE_BUFFER(
    IAudioRenderClient*             client,
    UINT32                          NumFramesWritten,
    DWORD                           dwFlags,
    PHYDRAHOOK_EVT_PRE_EXTENSION     Extension
);

typedef EVT_HYDRAHOOK_ARC_PRE_RELEASE_BUFFER *PFN_HYDRAHOOK_ARC_PRE_RELEASE_BUFFER;

typedef
_Function_class_(EVT_HYDRAHOOK_ARC_POST_RELEASE_BUFFER)
VOID
EVT_HYDRAHOOK_ARC_POST_RELEASE_BUFFER(
    IAudioRenderClient*             client,
    UINT32                          NumFramesWritten,
    DWORD                           dwFlags,
    PHYDRAHOOK_EVT_POST_EXTENSION    Extension
);

typedef EVT_HYDRAHOOK_ARC_POST_RELEASE_BUFFER *PFN_HYDRAHOOK_ARC_POST_RELEASE_BUFFER;


typedef struct _HYDRAHOOK_ARC_EVENT_CALLBACKS
{
    PFN_HYDRAHOOK_ARC_PRE_GET_BUFFER         EvtHydraHookARCPreGetBuffer;
    PFN_HYDRAHOOK_ARC_POST_GET_BUFFER        EvtHydraHookARCPostGetBuffer;
    
    PFN_HYDRAHOOK_ARC_PRE_RELEASE_BUFFER     EvtHydraHookARCPreReleaseBuffer;
    PFN_HYDRAHOOK_ARC_POST_RELEASE_BUFFER    EvtHydraHookARCPostReleaseBuffer;

} HYDRAHOOK_ARC_EVENT_CALLBACKS, *PHYDRAHOOK_ARC_EVENT_CALLBACKS;

VOID FORCEINLINE HYDRAHOOK_ARC_EVENT_CALLBACKS_INIT(
    _Out_ PHYDRAHOOK_ARC_EVENT_CALLBACKS Callbacks
)
{
    ZeroMemory(Callbacks, sizeof(HYDRAHOOK_ARC_EVENT_CALLBACKS));
}

#endif // HydraHookCoreAudio_h__
