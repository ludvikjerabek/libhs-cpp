/*
 * @file ExpressionInfo.h
 * @brief Wrapper for hs_expr_info_t to provides expression info
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

#ifndef LIBHS_EXPRESSION_INFO_H
#define LIBHS_EXPRESSION_INFO_H

#include <hs/hs.h>
#include <memory>
#include <exception>
#include <string>

namespace HyperScan {
    class Pattern;
    class ExtendedExpressionContext;
    class ExpressionInfo {
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
        explicit ExpressionInfo(const std::string &pattern, unsigned int flags);
        explicit ExpressionInfo(const std::string &pattern, unsigned int flags, const ExtendedExpressionContext &ext);
        explicit ExpressionInfo(const Pattern &sp);
        explicit ExpressionInfo(const Pattern &sp, const ExtendedExpressionContext &ext);
        ExpressionInfo(ExpressionInfo &&ei) = default;
        ExpressionInfo &operator=(ExpressionInfo &&ei) = default;
        ExpressionInfo(const ExpressionInfo &ei) = delete;
        ExpressionInfo &operator=(const ExpressionInfo &ei) = delete;
        ~ExpressionInfo() = default;
    public:
        [[nodiscard]] char GetMatchesAtEod() const;
        [[nodiscard]] char GetMatchesOnlyAtEod() const;
        [[nodiscard]] unsigned int GetMaxWidth() const;
        [[nodiscard]] unsigned int GetMinWidth() const;
        [[nodiscard]] char GetUnorderedMatches() const;
    private:
        struct Deleter {
            void operator()(hs_expr_info_t *ei) {
                free(ei);
            }
        };
        std::unique_ptr<hs_expr_info_t, Deleter> _info;
    };
}

#endif //LIBHS_EXPRESSION_INFO_H
