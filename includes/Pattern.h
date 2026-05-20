/*
 * @file Pattern.cpp
 * @brief Pattern class is used to define a single regex pattern and to crate the associated database for scanning.
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


#ifndef LIBHS_PATTERN_H
#define LIBHS_PATTERN_H

#include <hs/hs.h>
#include "Database.h"
#include "MultiLiteral.h"
#include <string>
#include <memory>

namespace HyperScan {
    class BlockDatabase;
    class VectorDatabase;
    class StreamDatabase;
    class ExpressionInfo;
    class PlatformInfo;
    class ExtendedExpressionContext;
    class Pattern {
        friend class Database;
        friend class ExpressionInfo;
    public:
        enum Flags : unsigned int {
            CASELESS = HS_FLAG_CASELESS,
            DOTALL = HS_FLAG_DOTALL,
            MULTILINE = HS_FLAG_MULTILINE,
            SINGLEMATCH = HS_FLAG_SINGLEMATCH,
            ALLOWEMPTY = HS_FLAG_ALLOWEMPTY,
            UTF8 = HS_FLAG_UTF8,
            UCP = HS_FLAG_UCP,
            PREFILTER = HS_FLAG_PREFILTER,
            LEFTMOST = HS_FLAG_SOM_LEFTMOST,
            COMBINATION = HS_FLAG_COMBINATION,
            QUIET = HS_FLAG_QUIET
        };
    public:
        Pattern();
        Pattern(std::string pattern, unsigned int flags);
        Pattern(std::string pattern, unsigned int flags, unsigned int id);
        ~Pattern() = default;
    public:
        [[nodiscard]] std::string GetPattern() const;
        void SetPattern(const std::string &pattern);
        [[nodiscard]] unsigned int GetFlags() const;
        void SetFlags(unsigned int flags);
        [[nodiscard]] unsigned int GetId() const;
        void SetId(unsigned int id);
        [[nodiscard]] ExpressionInfo GetExpressionInfo();
        [[nodiscard]] ExpressionInfo GetExpressionInfo(const ExtendedExpressionContext &ext);
        [[nodiscard]] BlockDatabase GetBlockDatabase();
        [[nodiscard]] VectorDatabase GetVectorDatabase();
        [[nodiscard]] StreamDatabase GetStreamDatabase(StreamDatabase::Horizon horizon = StreamDatabase::Horizon::NONE);
        [[nodiscard]] BlockDatabase GetBlockDatabase(const PlatformInfo &pi);
        [[nodiscard]] VectorDatabase GetVectorDatabase(const PlatformInfo &pi);
        [[nodiscard]] StreamDatabase GetStreamDatabase(const PlatformInfo &pi, StreamDatabase::Horizon horizon = StreamDatabase::Horizon::NONE);
    private:
        std::string _pattern;
        unsigned int _flags;
        unsigned int _id; // Not used unless you pass this to multi pattern
    };
}

#endif //LIBHS_PATTERN_H
