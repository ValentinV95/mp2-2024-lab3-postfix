#pragma once

#include <exception>
#include "arithmetic.h"

class inputException : public std::exception
{
private:
	int posLxException;
	const char* message;
	int codeError;
public:
	inputException(const char* msg, int codeError, int posLxException);
	const char* what() const noexcept override;
	int getPosLexemException() const noexcept;
	int getCodeError() const noexcept;
};