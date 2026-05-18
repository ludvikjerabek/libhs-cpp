/*
 * @file ExpressionExt.h
 * @brief Wrapper for hs_expr_ext_t to provided extended expression info
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

#ifndef LIBHS_EXPRESSIONEXT_H
#define LIBHS_EXPRESSIONEXT_H

#include <hs/hs.h>

namespace HyperScan {
    class ExtendedExpressionContext {
        friend class MultiPatternExtended;
        friend class ExpressionInfo;
    public:
        ExtendedExpressionContext();
        ~ExtendedExpressionContext() = default;
    public:
        [[nodiscard]] unsigned long long GetFlags() const;
        [[nodiscard]] unsigned long long GetMinOffset() const;
        [[nodiscard]] unsigned long long GetMaxOffset() const;
        [[nodiscard]] unsigned long long GetMinLength() const;
        [[nodiscard]] unsigned GetEditDistance() const;
        [[nodiscard]] unsigned GetHammingDistanced() const;
        void SetMinOffset(unsigned long long min_offset);
        void SetMaxOffset(unsigned long long max_offset);
        void SetMinLength(unsigned long long min_length);
        void SetEditDistance(unsigned edit_distance);
        void SetHammingDistanced(unsigned hamming_distance);
        void ClearMinOffset();
        void ClearMaxOffset();
        void ClearMinLength();
        void ClearEditDistance();
        void ClearHammingDistanced();
        [[nodiscard]] bool IsSetMinOffset() const;
        [[nodiscard]] bool IsSetMaxOffset() const;
        [[nodiscard]] bool IsSetMinLength() const;
        [[nodiscard]] bool IsSetEditDistance() const;
        [[nodiscard]] bool IsSetHammingDistanced() const;
    private:
        hs_expr_ext_t _ext;
    };
}

#endif //LIBHS_EXPRESSIONEXT_H
