/*
 * @file PlatformInfo.h
 * @brief PlatformInfo class is a wrapper for hs_platform_info_t.
 * @author Ludvik Jerabek
 * @version 1.0 04/08/2021
 *
 * MIT License
 *
 * Copyright (c) 2021 Ludvik Jerabek
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LIBHS_PLATFORMINFO_H
#define LIBHS_PLATFORMINFO_H

#include <hs/hs.h>

namespace HyperScan {
    class PlatformInfo {
        friend class Database;
    public:
        PlatformInfo();
        PlatformInfo(unsigned long long int features, unsigned long long int reserved1, unsigned long long int reserved2, unsigned int tune);
        ~PlatformInfo() = default;
    public:
        void Reset();
        [[nodiscard]] unsigned long long int GetCpuFeatures() const;
        [[nodiscard]] unsigned long long int GetReserved1() const;
        [[nodiscard]] unsigned long long int GetReserved2() const;
        [[nodiscard]] unsigned int GetTune() const;
        void SetCpuFeatures(unsigned long long int features);
        void SetReserved1(unsigned long long int reserved);
        void SetReserved2(unsigned long long int reserved);
        void SetTune(unsigned int tune);
    private:
        hs_platform_info_t _info;
    };
}

#endif //LIBHS_PLATFORMINFO_H
