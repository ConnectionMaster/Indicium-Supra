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


#ifndef HydraHookCore_h__
#define HydraHookCore_h__


#ifdef HYDRAHOOK_DYNAMIC
#ifdef HYDRAHOOK_EXPORTS
#define HYDRAHOOK_API __declspec(dllexport)
#else
#define HYDRAHOOK_API __declspec(dllimport)
#endif
#else
#define HYDRAHOOK_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum _HYDRAHOOK_ERRORS
    {
        HYDRAHOOK_ERROR_NONE = 0x20000000,
        HYDRAHOOK_ERROR_INVALID_ENGINE_HANDLE = 0xE0000001,
        HYDRAHOOK_ERROR_CREATE_THREAD_FAILED = 0xE0000002,
        HYDRAHOOK_ERROR_ENGINE_ALLOCATION_FAILED = 0xE0000003,
        HYDRAHOOK_ERROR_ENGINE_ALREADY_ALLOCATED = 0xE0000004,
        HYDRAHOOK_ERROR_INVALID_HMODULE_HANDLE = 0xE0000005,
        HYDRAHOOK_ERROR_REFERENCE_INCREMENT_FAILED = 0xE0000006,
        HYDRAHOOK_ERROR_CONTEXT_ALLOCATION_FAILED = 0xE0000007,
		HYDRAHOOK_ERROR_CREATE_EVENT_FAILED = 0xE0000008,

    } HYDRAHOOK_ERROR;

    typedef enum _HYDRAHOOK_D3D_VERSION {
        HydraHookDirect3DVersionUnknown = 0,
        HydraHookDirect3DVersion9 = 1 << 0,
        HydraHookDirect3DVersion10 = 1 << 1,
        HydraHookDirect3DVersion11 = 1 << 2,
        HydraHookDirect3DVersion12 = 1 << 3
    } HYDRAHOOK_D3D_VERSION, *PHYDRAHOOK_D3D_VERSION;

    //
    // HydraHook engine handle
    // 
    typedef struct _HYDRAHOOK_ENGINE *PHYDRAHOOK_ENGINE;

    //
    // Forward declarations of version-specific callbacks
    // 
    typedef struct _HYDRAHOOK_D3D9_EVENT_CALLBACKS *PHYDRAHOOK_D3D9_EVENT_CALLBACKS;
    typedef struct _HYDRAHOOK_D3D10_EVENT_CALLBACKS *PHYDRAHOOK_D3D10_EVENT_CALLBACKS;
    typedef struct _HYDRAHOOK_D3D11_EVENT_CALLBACKS *PHYDRAHOOK_D3D11_EVENT_CALLBACKS;
    typedef struct _HYDRAHOOK_D3D12_EVENT_CALLBACKS *PHYDRAHOOK_D3D12_EVENT_CALLBACKS;
    typedef struct _HYDRAHOOK_ARC_EVENT_CALLBACKS *PHYDRAHOOK_ARC_EVENT_CALLBACKS;

    typedef struct _HYDRAHOOK_EVT_PRE_EXTENSION
    {
        //
        // Internal engine handle
        // 
        PHYDRAHOOK_ENGINE    Engine;

        //
        // Custom context memory (if any, might be NULL)
        // 
        PVOID               Context;

    } HYDRAHOOK_EVT_PRE_EXTENSION, *PHYDRAHOOK_EVT_PRE_EXTENSION;

    /**
     * \fn  VOID FORCEINLINE HYDRAHOOK_EVT_PRE_EXTENSION_INIT( PHYDRAHOOK_EVT_PRE_EXTENSION Extension, PHYDRAHOOK_ENGINE Engine, PVOID Context )
     *
     * \brief   HydraHook event pre extension initialize
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    20.08.2019
     *
     * \param   Extension   The extension.
     * \param   Engine      The engine.
     * \param   Context     The context.
     *
     * \returns A FORCEINLINE.
     */
    VOID FORCEINLINE HYDRAHOOK_EVT_PRE_EXTENSION_INIT(
        PHYDRAHOOK_EVT_PRE_EXTENSION Extension,
        PHYDRAHOOK_ENGINE Engine,
        PVOID Context
    )
    {
        ZeroMemory(Extension, sizeof(HYDRAHOOK_EVT_PRE_EXTENSION));

        Extension->Engine = Engine;
        Extension->Context = Context;
    }

    typedef struct _HYDRAHOOK_EVT_POST_EXTENSION
    {
        //
        // Internal engine handle
        // 
        PHYDRAHOOK_ENGINE    Engine;

        //
        // Custom context memory (if any, might be NULL)
        // 
        PVOID               Context;

    } HYDRAHOOK_EVT_POST_EXTENSION, *PHYDRAHOOK_EVT_POST_EXTENSION;

    /**
     * \fn  VOID FORCEINLINE HYDRAHOOK_EVT_POST_EXTENSION_INIT( PHYDRAHOOK_EVT_POST_EXTENSION Extension, PHYDRAHOOK_ENGINE Engine, PVOID Context )
     *
     * \brief   HydraHook event post extension initialize
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    20.08.2019
     *
     * \param   Extension   The extension.
     * \param   Engine      The engine.
     * \param   Context     The native result.
     *
     * \returns A FORCEINLINE.
     *
     * ### param    NativeResult    The native result.
     */
    VOID FORCEINLINE HYDRAHOOK_EVT_POST_EXTENSION_INIT(
        PHYDRAHOOK_EVT_POST_EXTENSION Extension,
        PHYDRAHOOK_ENGINE Engine,
        PVOID Context
    )
    {
        ZeroMemory(Extension, sizeof(HYDRAHOOK_EVT_POST_EXTENSION));

        Extension->Engine = Engine;
        Extension->Context = Context;
    }

    typedef
        _Function_class_(EVT_HYDRAHOOK_GAME_HOOKED)
        VOID
        EVT_HYDRAHOOK_GAME_HOOKED(
            PHYDRAHOOK_ENGINE EngineHandle,
            const HYDRAHOOK_D3D_VERSION GameVersion
        );

    typedef EVT_HYDRAHOOK_GAME_HOOKED *PFN_HYDRAHOOK_GAME_HOOKED;

    typedef
        _Function_class_(EVT_HYDRAHOOK_GAME_UNHOOKED)
        VOID
        EVT_HYDRAHOOK_GAME_UNHOOKED(
            PHYDRAHOOK_ENGINE EngineHandle
        );

    typedef EVT_HYDRAHOOK_GAME_UNHOOKED *PFN_HYDRAHOOK_GAME_UNHOOKED;

    typedef
        _Function_class_(EVT_HYDRAHOOK_GAME_EXIT)
        VOID
        EVT_HYDRAHOOK_GAME_EXIT(
            PHYDRAHOOK_ENGINE EngineHandle
        );

    typedef EVT_HYDRAHOOK_GAME_EXIT *PFN_HYDRAHOOK_GAME_EXIT;

    typedef struct _HYDRAHOOK_ENGINE_CONFIG
    {
        //
        // Event callback invoked once a requested render API has been hooked successfully
        // 
        PFN_HYDRAHOOK_GAME_HOOKED EvtHydraHookGameHooked;

        //
        // Event callback invoked prior to unhooking the render API
        // 
        PFN_HYDRAHOOK_GAME_UNHOOKED EvtHydraHookGamePreUnhook;

        //
        // Event callback invoked after render API has been unhooked
        // 
        PFN_HYDRAHOOK_GAME_UNHOOKED EvtHydraHookGamePostUnhook;

        //
        // Event callback invoked when host process shutdown has been detected
        // 
        PFN_HYDRAHOOK_GAME_EXIT EvtHydraHookGamePreExit;

        struct
        {
            //
            // Enables detection and hooking of Direct3D 9 render pipeline, if used by host process
            // 
            BOOL HookDirect3D9;

            //
            // Enables detection and hooking of Direct3D 10 render pipeline, if used by host process
            // 
            BOOL HookDirect3D10;

            //
            // Enables detection and hooking of Direct3D 11 render pipeline, if used by host process
            // 
            BOOL HookDirect3D11;

            //
            // Enables detection and hooking of Direct3D 12 render pipeline, if used by host process
            // 
            BOOL HookDirect3D12;

        } Direct3D;

        struct
        {
        	//
        	// Enables hooking relevant Core Audio APIs
        	// 
            BOOL HookCoreAudio;

        } CoreAudio;

        struct
        {
        	//
        	// TRUE if log file should be generated, FALSE otherwise
        	// 
            BOOL IsEnabled;

        	//
        	// Full path and name to log file
        	// 
            PCSTR FilePath;

        } Logging;

    } HYDRAHOOK_ENGINE_CONFIG, *PHYDRAHOOK_ENGINE_CONFIG;

    /**
     * \fn  VOID FORCEINLINE HYDRAHOOK_ENGINE_CONFIG_INIT( PHYDRAHOOK_ENGINE_CONFIG EngineConfig )
     *
     * \brief   Initializes an HYDRAHOOK_ENGINE_CONFIG struct.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    30.07.2019
     *
     * \param   EngineConfig    The engine configuration.
     *
     * \returns Nothing.
     */
    VOID FORCEINLINE HYDRAHOOK_ENGINE_CONFIG_INIT(
        PHYDRAHOOK_ENGINE_CONFIG EngineConfig
    )
    {
        ZeroMemory(EngineConfig, sizeof(HYDRAHOOK_ENGINE_CONFIG));

        EngineConfig->Logging.IsEnabled = TRUE;
        EngineConfig->Logging.FilePath = "%TEMP%\\HydraHook.log";
    }

    /**
     * \fn  HYDRAHOOK_API HYDRAHOOK_ERROR HydraHookEngineCreate( _In_ HMODULE HostInstance, _In_ PHYDRAHOOK_ENGINE_CONFIG EngineConfig, _Out_opt_ PHYDRAHOOK_ENGINE* Engine );
     *
     * \brief   Initializes the HydraHook engine. Attempts too hook into the host process's render
     *          pipeline and optionally notifies the caller about progress via callbacks provided in
     *          HYDRAHOOK_ENGINE_CONFIG struct. Calling this function is expected to happen in
     *          DllMain() at DLL_PROCESS_ATTACH.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    01.08.2019
     *
     * \param           HostInstance    The host instance handle.
     * \param           EngineConfig    The engine configuration.
     * \param [in,out]  Engine          If non-null, the newly allocated engine handle.
     *
     * \returns An HYDRAHOOK_ERROR.
     */
    HYDRAHOOK_API HYDRAHOOK_ERROR HydraHookEngineCreate(
        _In_ HMODULE HostInstance,
        _In_ PHYDRAHOOK_ENGINE_CONFIG EngineConfig,
        _Out_opt_ PHYDRAHOOK_ENGINE* Engine
    );

    /**
     * \fn  HYDRAHOOK_API HYDRAHOOK_ERROR HydraHookEngineDestroy( _In_ HMODULE HostInstance );
     *
     * \brief   Frees all resources internally used by the engine. Reverts all established hooks and
     *          invokes the shutdown event callbacks. Calling this function is expected to happen in
     *          DllMain() at DLL_PROCESS_DETACH.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    02.08.2019
     *
     * \param   HostInstance    The host instance.
     *
     * \returns An HYDRAHOOK_ERROR.
     */
    HYDRAHOOK_API HYDRAHOOK_ERROR HydraHookEngineDestroy(
        _In_ HMODULE HostInstance
    );

    /**
     * \fn  HYDRAHOOK_API HYDRAHOOK_ERROR HydraHookEngineAllocCustomContext( _In_ PHYDRAHOOK_ENGINE Engine, _Out_ PVOID* Context, _In_ size_t ContextSize );
     *
     * \brief   Allocates a custom sized chunk of memory which will be accessible from all event
     *          callbacks during engine lifetime. Repeatedly calling this function will free
     *          previously allocated context memory.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    03.08.2019
     *
     * \param           Engine      The engine handle.
     * \param [in,out]  Context     If non-null, pointer to the newly allocated context memory.
     * \param           ContextSize Size of the context memory.
     *
     * \returns An HYDRAHOOK_ERROR.
     */
    HYDRAHOOK_API HYDRAHOOK_ERROR HydraHookEngineAllocCustomContext(
        _In_
        PHYDRAHOOK_ENGINE Engine,
        _Out_
        PVOID* Context,
        _In_
        size_t ContextSize
    );

    /**
     * \fn  HYDRAHOOK_API HYDRAHOOK_ERROR HydraHookEngineFreeCustomContext( _In_ PHYDRAHOOK_ENGINE Engine );
     *
     * \brief   Frees custom context memory for the supplied engine handle, if any.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    03.08.2019
     *
     * \param   Engine  The engine handle.
     *
     * \returns An HYDRAHOOK_ERROR.
     */
    HYDRAHOOK_API HYDRAHOOK_ERROR HydraHookEngineFreeCustomContext(
        _In_
        PHYDRAHOOK_ENGINE Engine
    );

    /**
     * \fn  HYDRAHOOK_API PVOID HydraHookEngineGetCustomContext( _In_ PHYDRAHOOK_ENGINE Engine );
     *
     * \brief   Returns a pointer to previously allocated custom context memory, or NULL if none
     *          available.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    03.08.2019
     *
     * \param   Engine  The engine handle.
     *
     * \returns A PVOID.
     */
    HYDRAHOOK_API PVOID HydraHookEngineGetCustomContext(
        _In_
        PHYDRAHOOK_ENGINE Engine
    );

#ifndef HYDRAHOOK_NO_D3D9

    /**
     * \fn  HYDRAHOOK_API VOID HydraHookEngineSetD3D9EventCallbacks( _In_ PHYDRAHOOK_ENGINE Engine, _In_ PHYDRAHOOK_D3D9_EVENT_CALLBACKS Callbacks );
     *
     * \brief   Registers one or more Direct3D 9(Ex) render pipeline callbacks.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    05.05.2019
     *
     * \param   Engine      The engine handle.
     * \param   Callbacks   The callback collection to register.
     *
     * \returns Nothing.
     */
    HYDRAHOOK_API VOID HydraHookEngineSetD3D9EventCallbacks(
        _In_
        PHYDRAHOOK_ENGINE Engine,
        _In_
        PHYDRAHOOK_D3D9_EVENT_CALLBACKS Callbacks
    );

#endif

#ifndef HYDRAHOOK_NO_D3D10

    /**
     * \fn  HYDRAHOOK_API VOID HydraHookEngineSetD3D10EventCallbacks( _In_ PHYDRAHOOK_ENGINE Engine, _In_ PHYDRAHOOK_D3D10_EVENT_CALLBACKS Callbacks );
     *
     * \brief   Registers one or more Direct3D 10 render pipeline callbacks.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    05.05.2019
     *
     * \param   Engine      The engine handle.
     * \param   Callbacks   The callback collection to register.
     *
     * \returns A VOID.
     */
    HYDRAHOOK_API VOID HydraHookEngineSetD3D10EventCallbacks(
        _In_
        PHYDRAHOOK_ENGINE Engine,
        _In_
        PHYDRAHOOK_D3D10_EVENT_CALLBACKS Callbacks
    );

#endif

#ifndef HYDRAHOOK_NO_D3D11

    /**
     * \fn  HYDRAHOOK_API VOID HydraHookEngineSetD3D11EventCallbacks( _In_ PHYDRAHOOK_ENGINE Engine, _In_ PHYDRAHOOK_D3D11_EVENT_CALLBACKS Callbacks );
     *
     * \brief   Registers one or more Direct3D 11 render pipeline callbacks.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    05.05.2019
     *
     * \param   Engine      The engine handle.
     * \param   Callbacks   The callback collection to register.
     *
     * \returns A VOID.
     */
    HYDRAHOOK_API VOID HydraHookEngineSetD3D11EventCallbacks(
        _In_
        PHYDRAHOOK_ENGINE Engine,
        _In_
        PHYDRAHOOK_D3D11_EVENT_CALLBACKS Callbacks
    );

#endif

#ifndef HYDRAHOOK_NO_D3D12

    /**
     * \fn  HYDRAHOOK_API VOID HydraHookEngineSetD3D12EventCallbacks( _In_ PHYDRAHOOK_ENGINE Engine, _In_ PHYDRAHOOK_D3D12_EVENT_CALLBACKS Callbacks );
     *
     * \brief   Registers one or more Direct3D 12 render pipeline callbacks.
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    05.05.2019
     *
     * \param   Engine      The engine handle.
     * \param   Callbacks   The callback collection to register.
     *
     * \returns A VOID.
     */
    HYDRAHOOK_API VOID HydraHookEngineSetD3D12EventCallbacks(
        _In_
        PHYDRAHOOK_ENGINE Engine,
        _In_
        PHYDRAHOOK_D3D12_EVENT_CALLBACKS Callbacks
    );

#endif

#ifndef HYDRAHOOK_NO_COREAUDIO

    HYDRAHOOK_API VOID HydraHookEngineSetARCEventCallbacks(
        _In_
        PHYDRAHOOK_ENGINE Engine,
        _In_
        PHYDRAHOOK_ARC_EVENT_CALLBACKS Callbacks
    );

#endif

    /**
     * \fn  HYDRAHOOK_API VOID HydraHookEngineLogDebug( _In_ LPCSTR Format, _In_opt_ ... );
     *
     * \brief   HydraHook engine log debug
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    16.05.2019
     *
     * \param   Format  Describes the format to use.
     * \param   ...     The ...
     *
     * \returns A VOID.
     */
    HYDRAHOOK_API VOID HydraHookEngineLogDebug(
        _In_
        LPCSTR Format,
        _In_opt_
        ...
    );

    /**
     * \fn  HYDRAHOOK_API VOID HydraHookEngineLogInfo( _In_ LPCSTR Format, _In_opt_ ... );
     *
     * \brief   HydraHook engine log information
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    16.05.2019
     *
     * \param   Format  Describes the format to use.
     * \param   ...     The ...
     *
     * \returns A VOID.
     */
    HYDRAHOOK_API VOID HydraHookEngineLogInfo(
        _In_
        LPCSTR Format,
        _In_opt_
        ...
    );

    /**
     * \fn  HYDRAHOOK_API VOID HydraHookEngineLogWarning( _In_ LPCSTR Format, _In_opt_ ... );
     *
     * \brief   HydraHook engine log warning
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    16.05.2019
     *
     * \param   Format  Describes the format to use.
     * \param   ...     The ...
     *
     * \returns A VOID.
     */
    HYDRAHOOK_API VOID HydraHookEngineLogWarning(
        _In_
        LPCSTR Format,
        _In_opt_
        ...
    );

    /**
     * \fn  HYDRAHOOK_API VOID HydraHookEngineLogError( _In_ LPCSTR Format, _In_opt_ ... );
     *
     * \brief   HydraHook engine log error
     *
     * \author  Benjamin HÃ¶glinger-Stelzer
     * \date    16.05.2019
     *
     * \param   Format  Describes the format to use.
     * \param   ...     The ...
     *
     * \returns A VOID.
     */
    HYDRAHOOK_API VOID HydraHookEngineLogError(
        _In_
        LPCSTR Format,
        _In_opt_
        ...
    );

#ifdef __cplusplus
}
#endif

#endif // HydraHookCore_h__
