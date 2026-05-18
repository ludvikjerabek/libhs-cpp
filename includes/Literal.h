/*
 * @file Literal.h
 * @brief Literal class is used to define literals and to crate the associated database for scanning.
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

#ifndef LIBHS_LITERAL_H
#define LIBHS_LITERAL_H

#include <hs/hs.h>
#include "Database.h"
#include "StreamDatabase.h"
#include <vector>
#include <memory>

namespace HyperScan {
    class BlockDatabase;
    class VectorDatabase;
    class StreamDatabase;
    class PlatformInfo;
    class Literal {
        friend class Database;
    public:
        enum Flags : unsigned int {
            CASELESS = HS_FLAG_CASELESS,
            SINGLEMATCH = HS_FLAG_SINGLEMATCH,
            LEFTMOST = HS_FLAG_SOM_LEFTMOST
        };
    public:
        explicit Literal();
        explicit Literal(std::vector<char> literal, unsigned int flags);
        explicit Literal(std::vector<char> literal, unsigned int flags, unsigned int id);
        ~Literal() = default;
    public:
        [[nodiscard]] std::vector<char> GetLiteral() const;
        void SetLiteral(const std::vector<char> &literal);
        [[nodiscard]] unsigned int GetFlags() const;
        void SetFlags(unsigned int flags);
        [[nodiscard]] unsigned int GetId() const;
        void SetId(unsigned int id);
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
        std::vector<char> _literal;
        unsigned int _flags;
        unsigned int _id;
    };
}

#endif //LIBHS_LITERAL_H
