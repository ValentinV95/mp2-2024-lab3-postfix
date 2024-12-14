#include "arithmetic.h"

//ID
// 0 - base class
// 1 - constant
// -1 - operand class
// 2 - variable
// 3,-3,4,-4 - sin,cos,tan,cot
// -2 - unar -
// 5,-5,6,-6 - -,+,*,/
// 7,-7 - (,)

TArithmeticExpression::TArithmeticExpression(const std::string& s) {
	expression = s;
	infix_form = Main_Parser(s);
};
void TArithmeticExpression::print_rpn() {
	for (auto& el : postfix_form) {
		el->print(true);
	}
	return;
};
void TArithmeticExpression::print_infix() {
	for (auto& el : infix_form) {
		el->print(true);
	}
	return;
};
void TArithmeticExpression::ToPostfix() {
	TDynamicStack<operation*> st;
	for (auto& el : infix_form) {
		if (el->isOperation()) {
			operation* op = dynamic_cast<operation*>(el);
			const int r = op->Get_Lexem_ID();
			if (r == -7) {
				while (!st.isEmpty() && st.Top()->Get_Lexem_ID() != 7) {
					postfix_form.push_back(st.Top());
					st.Pop();
				}
				st.Pop();
				if (st.size() > 0 && _is_func(st.Top()->Get_Lexem_ID())) {
					postfix_form.push_back(st.Top());
					st.Pop();
				}
				continue;
			}
			if (r == 7) {
				st.Push(op);
				continue;
			}
			while (!st.isEmpty() && op->getPriotiry() <= st.Top()->getPriotiry()) {
				postfix_form.push_back(st.Top());
				st.Pop();
			}
			st.Push(op);
		}
		else {
			const int r = el->Get_Lexem_ID();
			if (r == 1 || r == 2)
				postfix_form.push_back(el);
			else {
				st.Push(new operation(el->Get_VAL_NAME(), el->GetPos(), 0, true, false, el->Get_Lexem_ID()));
			}
		}
	}
	while (!st.isEmpty()) {
		postfix_form.push_back(st.Top());
		st.Pop();
	}
}
double TArithmeticExpression::simple_calc() {

	TDynamicStack<operand*> st;
	size_t ind = 0;
	while (ind < postfix_form.size() && !postfix_form.at(ind)->isOperation())
	{
		st.Push(dynamic_cast<operand*>(postfix_form[ind]));
		ind++;
	}
	for (; ind < postfix_form.size(); ind++) {

		if (postfix_form.at(ind)->isOperation()) {
			double x = st.Top()->getValue(), y = 1.0;
			if (postfix_form.at(ind)->Get_Lexem_ID() == -2) {
				x = -x;
				st.Pop();
				st.Push(new operand("", 0, x));
			}
			else {
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
				case 3:
					x = st.Top()->getValue();
					x = sin(x);
					st.Pop();
					st.Push(new operand("", 0, x));
					break;
				case -3:
					x = st.Top()->getValue();
					x = cos(x);
					st.Pop();
					st.Push(new operand("", 0, x));
					break;
				case 4:
					x = st.Top()->getValue();
					x = tan(x);
					st.Pop();
					st.Push(new operand("", 0, x));
					break;
				case -4:
					x = st.Top()->getValue();
					x = 1 / tan(x);
					st.Pop();
					st.Push(new operand("", 0, x));
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