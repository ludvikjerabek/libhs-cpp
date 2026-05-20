/*
 * @file Database.h
 * @brief Database base class. Wrapper for hs_database_t for HyperScan or VectorScan. This class should not be constructed directly.
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

#ifndef LIBHS_DATABASE_H
#define LIBHS_DATABASE_H

#include <hs/hs.h>
#include <memory>
#include <vector>

namespace HyperScan {
class MultiPattern;
class MultiPatternExtended;
class MultiLiteral;
class Pattern;
class Literal;
class Scratch;
class PlatformInfo;
class Database {
  friend class Scratch;
  friend class Scanner;
  friend class Stream;
 public:
  enum Type : unsigned int {
	STREAM = HS_MODE_STREAM,
	BLOCK = HS_MODE_BLOCK,
	VECTORED = HS_MODE_VECTORED
  };
  enum class Mode : unsigned int {
	STREAM_NONE   = HS_MODE_STREAM,
	STREAM_LARGE  = HS_MODE_STREAM | HS_MODE_SOM_HORIZON_LARGE,
	STREAM_MEDIUM = HS_MODE_STREAM | HS_MODE_SOM_HORIZON_MEDIUM,
	STREAM_SMALL  = HS_MODE_STREAM | HS_MODE_SOM_HORIZON_SMALL,
	BLOCK    = HS_MODE_BLOCK,
	VECTORED   = HS_MODE_VECTORED
  };
  static constexpr Type ExtractType(Mode mode) {
	return static_cast<Type>(
		static_cast<unsigned int>(mode) & (HS_MODE_STREAM | HS_MODE_BLOCK | HS_MODE_VECTORED)
	);
  }
 protected:
  explicit Database(const MultiPattern &mp, Mode mode);
  explicit Database(const MultiPattern &mp, Mode mode, const PlatformInfo &pi);
  explicit Database(const MultiPatternExtended &mpe, Mode mode);
  explicit Database(const MultiPatternExtended &mpe, Mode mode, const PlatformInfo &pi);
  explicit Database(const MultiLiteral &ml, Mode mode);
  explicit Database(const MultiLiteral &ml, Mode mode, const PlatformInfo &pi);
  explicit Database(const Pattern &sp, Mode mode);
  explicit Database(const Pattern &sp, Mode mode, const PlatformInfo &pi);
  explicit Database(const Literal &sl, Mode mode);
  explicit Database(const Literal &sl, Mode mode, const PlatformInfo &pi);
  Database(Database &&db) = default;
  Database &operator=(Database &&db) = default;
 public:
  Database() = delete;
  Database(const Database &db) = delete;
  Database &operator=(const Database &db) = delete;
  ~Database() = default;
 public:
  [[nodiscard]] Type GetType() const;
  [[nodiscard]] Scratch GetScratch() const;
  [[nodiscard]] size_t GetSize() const;
  [[nodiscard]] std::string GetInfo() const;
 private:
  struct Deleter {
	void operator()(hs_database *db) {
	  hs_free_database(db);
	}
  };
  std::unique_ptr<hs_database_t, Deleter> _db;
  Type _type;
};
}

#endif //LIBHS_DATABASE_H
