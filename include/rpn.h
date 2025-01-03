#pragma once
#include <iostream>
#include "stack.h"
#include "lexem.h"
#include <stdexcept>

Vector<Lexeme> toRPN(Vector<Lexeme> infix);