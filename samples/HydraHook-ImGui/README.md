# HydraHook-ImGui

ImGui overlay sample for DirectX 9, 10, and 11 games.

## About

Demonstrates how to render [Dear ImGui](https://github.com/ocornut/imgui) interfaces in foreign processes. This sample supports multiple DirectX versions and automatically detects the game's renderer.

## Usage

Build the project, then inject `HydraHook-ImGui.dll` into a target process using a DLL injector:

```powershell
.\Injector -i -n hl2.exe HydraHook-ImGui.dll
```

Replace `hl2.exe` with your target process name.
