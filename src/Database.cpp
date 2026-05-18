/*
 * @file Database.cpp
 * @brief Database base class. Wrapper for hs_database_t for HyperScan or VectorScan
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

#include "Database.h"
#include "Exceptions.h"
#include "Pattern.h"
#include "MultiPattern.h"
#include "MultiPatternExtended.h"
#include "Literal.h"
#include "MultiLiteral.h"
#include "Scratch.h"
#include "PlatformInfo.h"
#include <algorithm>

namespace HyperScan {
    Database::Database(const MultiPattern &mp, Mode mode) : _db(nullptr), _type(ExtractType(mode)) {
        std::vector<const char *> patterns;
        patterns.reserve(mp._patterns.size());
		for (const auto &pattern : mp._patterns) {
            patterns.push_back(pattern.c_str());
        }
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile_multi(patterns.data(), mp._flags.data(), mp._ids.data(), patterns.size(), static_cast<unsigned int>(mode), nullptr, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile_multi failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const MultiPattern &mp, Mode mode, const PlatformInfo &pi) : _db(nullptr), _type(ExtractType(mode)) {
        std::vector<const char *> patterns;
        patterns.reserve(mp._patterns.size());
		for (const auto &pattern : mp._patterns) {
            patterns.push_back(pattern.c_str());
        }
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile_multi(patterns.data(), mp._flags.data(), mp._ids.data(), patterns.size(),static_cast<unsigned int>(mode), &pi._info, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile_multi failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const MultiPatternExtended &mpe, Mode mode) : _db(nullptr), _type(ExtractType(mode)) {
        std::vector<const char *> patterns;
        patterns.reserve(mpe._patterns.size());
		for (const auto &pattern : mpe._patterns) {
            patterns.push_back(pattern.c_str());
        }
        std::vector<const hs_expr_ext_t *> exts;
        exts.reserve(mpe._exts.size());
		for (const auto &ext : mpe._exts) {
            exts.push_back(ext.get());
        }
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile_ext_multi(patterns.data(), mpe._flags.data(), mpe._ids.data(), exts.data(), patterns.size(), static_cast<unsigned int>(mode), nullptr, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile_ext_multi failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const MultiPatternExtended &mpe, Mode mode, const PlatformInfo &pi) : _db(nullptr), _type(ExtractType(mode)) {
        std::vector<const char *> patterns;
        patterns.reserve(mpe._patterns.size());
		for (const auto &pattern : mpe._patterns) {
            patterns.push_back(pattern.c_str());
        }
        std::vector<const hs_expr_ext_t *> exts;
        exts.reserve(mpe._exts.size());
		for (const auto &ext : mpe._exts) {
            exts.push_back(ext.get());
        }
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile_ext_multi(patterns.data(), mpe._flags.data(), mpe._ids.data(), exts.data(), patterns.size(), static_cast<unsigned int>(mode), &pi._info, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile_ext_multi failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const MultiLiteral &ml, Mode mode) : _db(nullptr), _type(ExtractType(mode)) {
        std::vector<const char *> literals;
        std::vector<std::size_t> sizes;
        for (const auto &pattern : ml._literals) {
            literals.push_back(pattern.data());
            sizes.push_back(pattern.size());
        }
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile_lit_multi(literals.data(), ml._flags.data(), ml._ids.data(), sizes.data(), ml._literals.size(), static_cast<unsigned int>(mode), nullptr, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile_lit_multi failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const MultiLiteral &ml, Mode mode, const PlatformInfo &pi) : _db(nullptr), _type(ExtractType(mode)) {
        std::vector<const char *> literals;
        std::vector<std::size_t> sizes;
        for (const auto &pattern : ml._literals) {
            literals.push_back(pattern.data());
            sizes.push_back(pattern.size());
        }
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile_lit_multi(literals.data(), ml._flags.data(), ml._ids.data(), sizes.data(), ml._literals.size(), static_cast<unsigned int>(mode), &pi._info, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile_lit_multi failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const Pattern &sp, Mode mode) : _db(nullptr), _type(ExtractType(mode)) {
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile(sp._pattern.c_str(), sp._flags, static_cast<unsigned int>(mode), nullptr, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const Pattern &sp, Mode mode, const PlatformInfo &pi) : _db(nullptr), _type(ExtractType(mode)) {
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile(sp._pattern.c_str(), sp._flags, static_cast<unsigned int>(mode), &pi._info, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const Literal &sl, Mode mode) : _db(nullptr), _type(ExtractType(mode)) {
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile_lit(sl._literal.data(), sl._flags, sl._literal.size(), static_cast<unsigned int>(mode), nullptr, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile_lit failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Database::Database(const Literal &sl, Mode mode, const PlatformInfo &pi) : _db(nullptr), _type(ExtractType(mode)) {
        hs_compile_error_t *error = nullptr;
        hs_database_t *db = nullptr;
        hs_error_t hs_code = hs_compile_lit(sl._literal.data(), sl._flags, sl._literal.size(), static_cast<unsigned int>(mode), &pi._info, &db, &error);
        _db.reset(db);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_compile_lit failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw DatabaseException(e, hs_error, hs_code);
        }
    }

    Scratch Database::GetScratch() const {
        return Scratch(*this);
    }

    size_t Database::GetSize() const {
        size_t size = 0;
        hs_error_t hs_code = hs_database_size(_db.get(), &size);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_database_size failed";
            int hs_error = 0;
            throw DatabaseException(e, hs_error, hs_code);
        }
        return size;
    }

    std::string Database::GetInfo() const
	{
		char* strinfo = nullptr;
		hs_error_t hs_code = hs_database_info(_db.get(), &strinfo);
		if (hs_code!=HS_SUCCESS) {
			std::string e = "Call to hs_database_info failed";
			int hs_error = 0;
			throw DatabaseException(e, hs_error, hs_code);
		}
		std::string info(strinfo);
		free(strinfo);
		return info;
	}

Database::Type Database::GetType() const {
  return _type;
}

}