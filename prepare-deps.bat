@echo off
REM Install vcpkg dependencies. Run this from "x64 Native Tools Command Prompt for VS"
REM (or "Developer Command Prompt for VS") before building from Visual Studio.
REM
REM The first build from VS may fail with "unable to detect the active compiler"
REM because vcpkg runs in a context where the compiler toolchain is not set up.
REM Running this script once populates vcpkg_installed; subsequent VS builds work.

setlocal
cd /d "%~dp0"

if not exist "vcpkg\vcpkg.exe" (
    echo Bootstrapping vcpkg...
    call vcpkg\bootstrap-vcpkg.bat
    if errorlevel 1 (
        echo Bootstrap failed.
        exit /b 1
    )
)

REM vcpkg manifest mode keeps only one triplet; install x64 last so x64 builds work.
REM For Win32 builds, run: vcpkg\vcpkg.exe install --triplet x86-windows-static
echo Installing dependencies for x64-windows-static...
vcpkg\vcpkg.exe install --triplet x86-windows-static
if errorlevel 1 exit /b 1
vcpkg\vcpkg.exe install --triplet x64-windows-static
if errorlevel 1 exit /b 1

echo.
echo Dependencies installed. You can now build from Visual Studio.
exit /b 0
