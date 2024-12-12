#pragma once
#include "parse_string.h"
#include "stack.h"
#include <iostream>
// объ€вление функций и классов дл€ вычислени€ арифметических выражений

class TArithmeticExpression {
	
	vector<lexem*> infix_form;
	vector<lexem*> postfix_form;
	std::string expression;
public:

	TArithmeticExpression(const std::string& s) {
		expression = s;
		infix_form = Main_Parser(s);
	}
	void print_rpn() {
		for (auto& el : postfix_form) {
			el->print(true);
		}
		return;
	}
	void print_infix() {
		for (auto& el : infix_form) {
			el->print(true);
		}
		return;
	}

	void ToPostfix() {

//ID
// 0 - base class
// 1 - constant
// -1 - operand class
// 2 - variable
// 3,-3,4,-4 - sin,cos,tan,cot
// -2 - unar -
// 5,-5,6,-6 - -,+,*,/
// 7,-7 - (,)
		TDynamicStack<operation*> st;
		for (auto& el : infix_form) {
			for (auto& el : postfix_form) {
				el->print(true);
			}
			std::cout << '\n';
			for (int i = 0; i < st.size(); i++) {
				st.mem.at(i)->print(true);
			}
			std::cout << "\n";
			if (el->isOperation()) {
				operation* op = dynamic_cast<operation*>(el);
				int r = op->Get_Lexem_ID();
				//if (r == -2)continue;
				if (r == -7) {
					while (!st.isEmpty()&&st.Top()->Get_Lexem_ID()!=7) {
						postfix_form.push_back(st.Top());
						st.Pop();
					}
					st.Pop();
					continue;
				}
				if (r == 7) {
					st.Push(op);
					continue;
				}
				while (!st.isEmpty() && op->getPriotiry() <=st.Top()->getPriotiry()) {
					postfix_form.push_back(st.Top());
					st.Pop();
				}
				st.Push(op);
			}
			else {
				postfix_form.push_back(el);
			}
		}
		while (!st.isEmpty()) {
			postfix_form.push_back(st.Top());
			st.Pop();
		}
	}
	double simple_calc() {
		
		TDynamicStack<operand*> st;
		size_t ind = 0;
		while (ind < postfix_form.size() && !postfix_form.at(ind)->isOperation())
		{
			st.Push(dynamic_cast<operand*>(postfix_form[ind]));
			ind++;
		}
		for (; ind < postfix_form.size(); ind++) {

			if (postfix_form.at(ind)->isOperation()) {
				if (postfix_form.at(ind)->isUnar()) {
					double x = st.Top()->getValue();
					if (postfix_form.at(ind)->Get_Lexem_ID() == -2) {
						x = -x;
					}
					st.Pop();
					st.Push(new operand("", 0, x));
				}
				else {
					double x,y;
					switch (postfix_form.at(ind)->Get_Lexem_ID())
					{
					default:
						break;
					case 5:
						x = st.Top()->getValue();
						st.Pop();
						y = st.Top()->getValue();
						st.Pop();
						st.Push(new operand("", 0, y - x));
						break;
					case -5:
						x = st.Top()->getValue();
						st.Pop();
						y = st.Top()->getValue();
						st.Pop();
						st.Push(new operand("", 0, x + y));
						break;
					case 6:
						x = st.Top()->getValue();
						st.Pop();
						y = st.Top()->getValue();
						st.Pop();
						st.Push(new operand("", 0, x * y));
						break;
					case -6:
						x = st.Top()->getValue();
						st.Pop();
						y = st.Top()->getValue();
						st.Pop();
						st.Push(new operand("", 0, y / x));
						break;
					}


				}
			}
			else {
				st.Push(dynamic_cast<operand*>(postfix_form[ind]));
			}

		}
		return st.Top()->getValue();
	}
};