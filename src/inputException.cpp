#include "inputException.h"

//code errors:
//1 - the operand for this operation is lost
//2 - the operation before this operand was skipped
//3 - there is no opening bracket for this closing bracket
//4 - a constant was entered incorrectly
//5 - there is no closing bracket for this opening bracket
//6 - invalid character
//7 - the expression in parentheses is lost
//8 - the operation before this function was skipped
//9 - the opening parenthesis before the unary minus was skipped
//10 - the opening parenthesis for this function was skipped
inputException::inputException(const char* msg, int codeError, int posLxException) : message(msg), codeError(codeError), posLxException(posLxException) { }

const char* inputException::what() const noexcept
{
    return message;
}

int inputException::getPosLexemException() const noexcept
{
    return posLxException;
}