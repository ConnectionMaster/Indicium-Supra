/*
MIT License

Copyright (c) 2018-2026 Benjamin Höglinger-Stelzer

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

/**
 * @file Window.h
 * @brief Minimal window creation for Direct3D device detection.
 *
 * Creates a hidden window used to instantiate D3D devices when probing
 * for the host's render pipeline. Required for D3D9 CreateDevice.
 *
 * @internal
 */

#pragma once

#include <string>
#include <Windows.h>

/**
 * @brief Minimal Win32 window for D3D device creation.
 */
class Window
{
    WNDCLASSEX window_class{};
    HWND temp_window;
    std::string window_class_name;

public:
    /**
     * @brief Creates a hidden window with the given class name.
     * @param windowClassName Unique window class name for registration.
     */
    Window(std::string windowClassName);

    /** @brief Returns the window handle. */
    HWND windowHandle() const;

    /** @brief Destroys the window and unregisters the class. */
    ~Window();
};

