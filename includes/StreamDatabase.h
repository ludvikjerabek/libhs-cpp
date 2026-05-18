/*
 * @file StreamDatabase.h
 * @brief Derived from Database class provides StreamDatabase functions for HyperScan or VectorScan
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


#ifndef LIBHS_STREAMDATABASE_H
#define LIBHS_STREAMDATABASE_H

#include "Database.h"
#include "Stream.h"

namespace HyperScan {
    class Stream;
    class StreamDatabase final : public Database {
	public:
	  enum Horizon : unsigned int {
		NONE = 0,
		LARGE = HS_MODE_SOM_HORIZON_LARGE,
		MEDIUM = HS_MODE_SOM_HORIZON_MEDIUM,
		SMALL = HS_MODE_SOM_HORIZON_SMALL
	  };
	  static constexpr Mode GetStreamMode(Horizon horizon) {
		return static_cast<Mode>(HS_MODE_STREAM | static_cast<unsigned int>(horizon));
	  }
    public:
        explicit StreamDatabase(const MultiPattern &mp, Horizon horizon = Horizon::NONE) : Database(mp, GetStreamMode(horizon)) {};
        explicit StreamDatabase(const MultiPattern &mp, const PlatformInfo &pi, Horizon horizon = Horizon::NONE) : Database(mp, GetStreamMode(horizon), pi) {};
        explicit StreamDatabase(const MultiPatternExtended &mpe, Horizon horizon = Horizon::NONE) : Database(mpe, GetStreamMode(horizon)) {};
        explicit StreamDatabase(const MultiPatternExtended &mpe, const PlatformInfo &pi, Horizon horizon = Horizon::NONE) : Database(mpe, GetStreamMode(horizon), pi) {};
        explicit StreamDatabase(const MultiLiteral &ml, Horizon horizon = Horizon::NONE) : Database(ml,GetStreamMode(horizon)) {};
        explicit StreamDatabase(const MultiLiteral &ml, const PlatformInfo &pi, Horizon horizon = Horizon::NONE) : Database(ml, GetStreamMode(horizon), pi) {};
        explicit StreamDatabase(const Pattern &sp, Horizon horizon = Horizon::NONE) : Database(sp, GetStreamMode(horizon)) {};
        explicit StreamDatabase(const Pattern &sp, const PlatformInfo &pi, Horizon horizon = Horizon::NONE) : Database(sp, GetStreamMode(horizon), pi) {};
        explicit StreamDatabase(const Literal &sl, Horizon horizon = Horizon::NONE) : Database(sl, GetStreamMode(horizon)) {};
        explicit StreamDatabase(const Literal &sl, const PlatformInfo &pi, Horizon horizon = Horizon::NONE) : Database(sl, GetStreamMode(horizon), pi) {};
        StreamDatabase() = delete;
        StreamDatabase(const StreamDatabase &db) = delete;
        StreamDatabase &operator=(const StreamDatabase &db) = delete;
        StreamDatabase(StreamDatabase &&db) = default;
        StreamDatabase &operator=(StreamDatabase &&db) = default;
        ~StreamDatabase() = default;
    };
}

#endif //LIBHS_STREAMDATABASE_H
