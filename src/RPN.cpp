#include "RPN.h"
#include "stack.h"
#include <stdexcept>

void RPN::toRpn() {
	myStack<operation*> st; // stack
	for (size_t i = 0; i < infix.size(); ++i) { // infix lexem array
		if (infix[i]->getSym() == "(") { // '(' - in stack immediatly
			st.push(dynamic_cast<operation*>(infix[i]));
		}
		else if (infix[i]->getSym() == ")") { // ')' - 
			if (st.isEmpty()) throw std::invalid_argument(std::to_string(infix[i]->getPos()) + "ENo opening bracket for this bracket");
			while (st.top()->getSym() != "(") { // untill ( is found
				postfix.push_back(st.pop()); // pull all lexems out of stack and write it into postfix
				if (st.isEmpty()) throw std::invalid_argument(std::to_string(infix[i]->getPos()) + "ENo opening bracket for this bracket");
			}
			st.pop(); // pull (, but not writing in stack
		}
		else if (infix[i]->isOperation()) { // if it is an opertion
			while (!st.isEmpty() && (st.top()->getPriority() >= dynamic_cast<operation*>(infix[i])->getPriority())) { // >=
				postfix.push_back(st.pop()); // pull out all operations, that have higher or equal priority
			}
			st.push(dynamic_cast<operation*>(infix[i])); // write an operand to stack
		}
		else { // if it is an operand
			postfix.push_back(infix[i]); // write to postfix
		}
	}
	while (!st.isEmpty()) {
		if (st.top()->getSym() == "(") throw std::invalid_argument(std::to_string(st.top()->getPos()) + "ENo closing bracket for this bracket");
		postfix.push_back(st.pop());
	}
}
RPN::RPN(const myVector<lexem*>& s) : infix(s), postfix() { toRpn(); }
const myVector<lexem*>& RPN::getPostfix() const noexcept { return postfix; };
double RPN::calculate() {
	myVector<double> operands;
	myStack<double> st;
	operation* tmpOperator;
	operand* tmpOperand;
	for (size_t i = 0; i < postfix.size(); ++i) {
		if (!postfix[i]->isOperation()) // is operand
			st.push(dynamic_cast<operand*>(postfix[i])->getValue());
		else { // is operation
			tmpOperator = dynamic_cast<operation*>(postfix[i]);
			operands.resize(0);
			for (int _ = 0; _ < tmpOperator->getOperandsCount(); ++_) {
				if (st.isEmpty()) throw std::invalid_argument(std::to_string(tmpOperator->getSym().length()) + "L" + std::to_string(tmpOperator->getPos()) + "ENo operand for this operator");
				operands.push_back(st.pop());
			}
			st.push(tmpOperator->execute(operands));
		}
	}
	if (st.isEmpty()) throw std::invalid_argument("-1ENot enough operands");
	double tmp = st.pop();
	if (!st.isEmpty()) {
		tmp = st.pop();
		throw std::invalid_argument("-1EToo many operands");
	}
	return tmp;
}