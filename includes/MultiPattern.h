/*
 * @file MultiPattern.cpp
 * @brief MultiPattern class is used to define sets of regex patterns and to crate the associated database for scanning.
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

#ifndef LIBHS_MULTI_PATTERN_H
#define LIBHS_MULTI_PATTERN_H

#include "Database.h"
#include "StreamDatabase.h"
#include <string>
#include <vector>
#include <memory>

namespace HyperScan {
    class BlockDatabase;
    class VectorDatabase;
    class StreamDatabase;
    class PlatformInfo;
    class MultiPattern {
        friend class Database;
    public:
        MultiPattern() = default;
        ~MultiPattern() = default;
    public:
        void AddPattern(const std::string &pattern, unsigned flags, unsigned identifier);
        void Clear();
        [[nodiscard]] BlockDatabase GetBlockDatabase();
        [[nodiscard]] VectorDatabase GetVectorDatabase();
        [[nodiscard]] StreamDatabase GetStreamDatabase(StreamDatabase::Horizon horizon = StreamDatabase::Horizon::NONE);
        [[nodiscard]] BlockDatabase
        GetBlockDatabase(const PlatformInfo &pi);
        [[nodiscard]] VectorDatabase
        GetVectorDatabase(const PlatformInfo &pi);
        [[nodiscard]] StreamDatabase
        GetStreamDatabase(const PlatformInfo &pi, StreamDatabase::Horizon horizon = StreamDatabase::Horizon::NONE);
    private:
        std::vector<std::string> _patterns;
        std::vector<unsigned int> _flags;
        std::vector<unsigned int> _ids;
    };
}

#endif //LIBHS_MULTI_PATTERN_H
