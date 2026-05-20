/*
 * @file Stream.h
 * @brief Stream class wraps hs_stream_t
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

#ifndef LIBHS_STREAM_H
#define LIBHS_STREAM_H

#include "Exceptions.h"
#include "IScanner.h"
#include <hs/hs.h>
#include <memory>

namespace HyperScan {
    class Database;
    class Scratch;
    class StreamDatabase;
    class Stream : public IScanner {
        friend class Scanner;
    public:
        Stream();
        Stream(Stream &&scratch) = default;
        Stream &operator=(Stream &&scratch) = default;
        Stream(const Stream &scratch) = delete;
        Stream &operator=(const Stream &scratch) = delete;
        ~Stream() = default;
        void Open(const StreamDatabase &db);
        Stream Clone();
        void Reset();
        void Reset(const Scratch& scratch);
        void Reset(const Scratch& scratch, IMatcher& matcher);
        void Close();
        void Close(const Scratch& scratch);
        void Close(const Scratch& scratch, IMatcher& matcher);
    private:
        // Used for cloning
        explicit Stream(hs_stream_t *stream);
    private:
        struct Deleter {
            void operator()(hs_stream_t* stream) {
                // Always best if close is called, but we will try to free the memory.
                hs_close_stream(stream, nullptr, nullptr, nullptr);
            }
        };
    private:
        std::unique_ptr<hs_stream_t,Deleter> _stream;
    };
}

#endif //LIBHS_STREAM_H
