/*
 * @file HyperScan.h
 * @brief Primary include file needed to use the HyperScan or VectorScan C++ wrapper
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

#ifndef LIBHS_H
#define LIBHS_H

#include "Exceptions.h"
#include "PlatformInfo.h"
#include "Pattern.h"
#include "MultiPattern.h"
#include "MultiPatternExtended.h"
#include "Literal.h"
#include "MultiLiteral.h"
#include "ExpressionInfo.h"
#include "BlockDatabase.h"
#include "StreamDatabase.h"
#include "VectorDatabase.h"
#include "Scratch.h"
#include "Stream.h"
#include "Scanner.h"
#include "ExtendedExpressionContext.h"

namespace HyperScan {
    std::string GetVersion() {
        return hs_version();
    }
    bool ValidPlatform() {
        hs_error_t hs_code = hs_valid_platform();
        return (hs_code == HS_SUCCESS);
    }
}
#endif //LIBHS_H
