@echo off
@setlocal

set MYDIR=%~dp0
pushd "%MYDIR%"

set INJECT_X64=".\bin\x64\Injector.exe"
set INJECT_X86=".\bin\x86\Injector.exe"
set IMGUI_LIB="HydraHook-ImGui.dll"

%INJECT_X64% -n BEHEMOTH.exe -i %IMGUI_LIB%
%INJECT_X64% -n Ryse.exe -i %IMGUI_LIB%
%INJECT_X64% -n RoadRedemption.exe -i %IMGUI_LIB%
%INJECT_X86% -n hl2.exe -i %IMGUI_LIB%
%INJECT_X86% -n Bioshock2.exe -i %IMGUI_LIB%

popd
endlocal