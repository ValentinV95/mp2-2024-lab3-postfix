#pragma once
#include "lexem.h"
string PreParse(string const& s);
double NumParse(string const& s);
Vec<lexem*> MainParse(string const& s);
void Push_Stm(Vec<lexem*>& RES, Vec<operation*>& StmBuff, MyStack<lexem*>& LBuff, MyStack<operand*>& SOp, operation*& _stm, operand*& lhs, operand*& rhs, size_t& k);
void Push_Buff(Vec<lexem*>& RES, Vec<operation*>& StmBuff, MyStack<lexem*>& LBuff);