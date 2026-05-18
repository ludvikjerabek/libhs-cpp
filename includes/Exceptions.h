/*
 * @file Exceptions.h
 * @brief HyperScan or VectorScan exceptions used by various class objects
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

#ifndef LIBHS_EXCEPTIONS_H
#define LIBHS_EXCEPTIONS_H

#include <exception>
#include <string>

namespace HyperScan {
class DatabaseException : public std::exception {
public:
	DatabaseException(std::string msg, int hs_error, int hs_code)
			:_msg(std::move(msg)), _hs_error(hs_error), _hs_code(hs_code) { }
	~DatabaseException() override = default;
	[[nodiscard]] int getCode() const { return _hs_code; }
	[[nodiscard]] int getError() const { return _hs_error; }
	[[nodiscard]] const char* what() const noexcept override
	{
		return _msg.c_str();
	}
private:
	std::string _msg;
	int _hs_error;
	int _hs_code;
};

class DatabaseSerializerException : public std::exception {
public:
	DatabaseSerializerException(std::string msg, int hs_error, int hs_code)
			:_msg(std::move(msg)), _hs_error(hs_error), _hs_code(hs_code) { }
	~DatabaseSerializerException() override = default;
	[[nodiscard]] int getCode() const { return _hs_code; }
	[[nodiscard]] int getError() const { return _hs_error; }
	[[nodiscard]] const char* what() const noexcept override
	{
		return _msg.c_str();
	}
private:
	std::string _msg;
	int _hs_error;
	int _hs_code;
};

class ScratchException : public std::exception {
public:
	ScratchException(std::string msg, int hs_code)
			:_msg(std::move(msg)), _hs_code(hs_code) { }
	~ScratchException() override = default;
	[[nodiscard]] int getCode() const { return _hs_code; }
	[[nodiscard]] const char* what() const noexcept override
	{
		return _msg.c_str();
	}
private:
	std::string _msg;
	int _hs_code;
};

class StreamException : public std::exception {
public:
	StreamException(std::string msg, int hs_code)
			:_msg(std::move(msg)), _hs_code(hs_code) { }
	~StreamException() override = default;
	[[nodiscard]] int getCode() const { return _hs_code; }
	[[nodiscard]] const char* what() const noexcept override
	{
		return _msg.c_str();
	}
private:
	std::string _msg;
	int _hs_code;
};

class PlatformInfoException : public std::exception {
public:
	PlatformInfoException(std::string msg, int hs_code)
			:_msg(std::move(msg)), _hs_code(hs_code) { }
	~PlatformInfoException() override = default;
	[[nodiscard]] int getCode() const { return _hs_code; }
	[[nodiscard]] const char* what() const noexcept override
	{
		return _msg.c_str();
	}

private:
	std::string _msg;
	int _hs_code;
};

class ExpressionInfoException : public std::exception {
public:
	ExpressionInfoException(std::string msg, int hs_error, int hs_code)
			:_msg(std::move(msg)), _hs_error(hs_error), _hs_code(hs_code) { }
	~ExpressionInfoException() override = default;
	[[nodiscard]] int getCode() const { return _hs_code; }
	[[nodiscard]] int getError() const { return _hs_error; }
	[[nodiscard]] const char* what() const noexcept override
	{
		return _msg.c_str();
	}
private:
	std::string _msg;
	int _hs_error;
	int _hs_code;
};
}

#endif //LIBHS_EXCEPTIONS_H
