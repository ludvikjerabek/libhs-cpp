/*
 * @file Scratch.h
 * @brief Scratch class wrapper for hs_scratch_t for HyperScan or VectorScan
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

#ifndef LIBHS_SCRATCH_H
#define LIBHS_SCRATCH_H

#include <hs/hs.h>
#include <memory>

namespace HyperScan {
    class Database;
    class Scratch {
        friend class Scanner;
        friend class Stream;
    public:
        explicit Scratch(const Database &db);
        Scratch(Scratch &&scratch) = default;
        Scratch &operator=(Scratch &&scratch) = default;
        Scratch(const Scratch &scratch) = delete;
        Scratch &operator=(const Scratch &scratch) = delete;
        ~Scratch() = default;
    public:
        void Alloc(const Database &db);
        Scratch Clone();
    private:
        // Used by Scratch object to clone
        explicit Scratch(hs_scratch_t *scratch);
    private:
        struct Deleter {
            void operator()(hs_scratch_t *db) {
                hs_free_scratch(db);
            }
        };
        std::unique_ptr<hs_scratch_t, Deleter> _scratch;
    };
}

#endif //LIBHS_SCRATCH_H
