/*
 * @file Scratch.cpp
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

#include "Scratch.h"
#include "Database.h"
#include "Exceptions.h"

namespace HyperScan {
    Scratch::Scratch(hs_scratch_t *scratch) : _scratch(scratch) {}
    Scratch::Scratch(const Database &db) : _scratch(nullptr) {
        hs_scratch_t *scratch = nullptr;
        hs_error_t hs_code = hs_alloc_scratch(db._db.get(), &scratch);
        _scratch.reset(scratch);
        if (hs_code != HS_SUCCESS)
            throw ScratchException("Failed to hs_alloc_scratch failed", hs_code);
    }
    void Scratch::Alloc(const Database &db) {
        hs_scratch_t *scratch = _scratch.get();
        hs_error_t hs_code = hs_alloc_scratch(db._db.get(), &scratch);
        if (hs_code != HS_SUCCESS)
            throw ScratchException("Failed to hs_alloc_scratch failed", hs_code);
    }
    Scratch Scratch::Clone() {
        hs_scratch_t *scratch = nullptr;
        hs_error_t hs_code = hs_clone_scratch(_scratch.get(), &scratch);
        Scratch s(scratch);
        if (hs_code != HS_SUCCESS)
            throw ScratchException("Failed to hs_clone_scratch failed", hs_code);
        return s;
    }
}