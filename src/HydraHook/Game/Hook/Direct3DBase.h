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
 * @file Direct3DBase.h
 * @brief Abstract base for Direct3D version-specific hook implementations.
 *
 * Provides common interface for vtable-based hooking of Direct3D devices.
 * Subclasses return vtable indices for Present, Reset, etc.
 *
 * @internal
 */

#pragma once

#include "Window.h"
#include <vector>
#include <memory>


namespace Direct3DHooking
{
    /**
     * @brief Abstract base for Direct3D hook implementations.
     */
    class Direct3DBase
    {
    protected:
        std::unique_ptr<Window> temp_window;  /**< Temporary window for device creation. */
        virtual ~Direct3DBase() {}

    public:
        Direct3DBase() {}

        /**
         * @brief Returns vtable indices for hookable methods (Present, Reset, etc.).
         * @return Vector of vtable offsets to hook.
         */
        virtual std::vector<size_t> vtable() const = 0;
    };
}
