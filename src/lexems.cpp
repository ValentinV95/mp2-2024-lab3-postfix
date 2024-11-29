#include "lexems.h"
#include "parser.h"
#include <stdexcept>
#include <cmath>

lexem::lexem(const std::string& s, int p) : sym(s), pos(p) {}
const std::string& lexem::getSym() const noexcept { return sym; }
const int& lexem::getPos() const noexcept { return pos; }
lexem::~lexem() {}

void operation::fillOperations() {
	availableOperations.push_back("+");
	availableOperations.push_back("-");
	availableOperations.push_back("~");
	availableOperations.push_back("*");
	availableOperations.push_back("/");
	availableOperations.push_back("sin");
	availableOperations.push_back("cos");
	availableOperations.push_back("exp");
	availableOperations.push_back("pow");
	availableOperations.push_back("log");
	availableOperations.push_back("(");
	availableOperations.push_back(")");

	priotities.push_back(1);
	priotities.push_back(1);
	priotities.push_back(3);
	priotities.push_back(2);
	priotities.push_back(2);
	priotities.push_back(3);
	priotities.push_back(3);
	priotities.push_back(3);
	priotities.push_back(3);
	priotities.push_back(3);
	priotities.push_back(0);
	priotities.push_back(0);

	vOperandsCount.push_back(2);
	vOperandsCount.push_back(2);
	vOperandsCount.push_back(1);
	vOperandsCount.push_back(2);
	vOperandsCount.push_back(2);
	vOperandsCount.push_back(1);
	vOperandsCount.push_back(1);
	vOperandsCount.push_back(1);
	vOperandsCount.push_back(2);
	vOperandsCount.push_back(1);
	vOperandsCount.push_back(0);
	vOperandsCount.push_back(0);

	vCanBeAfterOperand.push_back(true);
	vCanBeAfterOperand.push_back(true);
	vCanBeAfterOperand.push_back(false);
	vCanBeAfterOperand.push_back(true);
	vCanBeAfterOperand.push_back(true);
	vCanBeAfterOperand.push_back(false);
	vCanBeAfterOperand.push_back(false);
	vCanBeAfterOperand.push_back(false);
	vCanBeAfterOperand.push_back(false);
	vCanBeAfterOperand.push_back(false);
	vCanBeAfterOperand.push_back(false);
	vCanBeAfterOperand.push_back(true);
}
operation::operation(const std::string& s, int p) : lexem(s, p) {
	for (size_t i = 0; i < availableOperations.size(); ++i) {
		if (this->getSym() == availableOperations[i]) {
			priority = priotities[i];
			operandsCount = vOperandsCount[i];
			break;
		}
	}
}
bool operation::isOperation() {
	return true;
}
bool operation::isOperation(const std::string& s) {
	for (size_t i = 0; i < availableOperations.size(); ++i)
		if (s == availableOperations[i])
			return true;
	return false;
}
bool operation::canBeAfterOperand(const std::string& s) {
	for (size_t i = 0; i < availableOperations.size(); ++i)
		if (s == availableOperations[i])
			return static_cast<bool>(vCanBeAfterOperand[i]);
	return false;
}
int operation::getPriority() noexcept {
	return priority;
}
int operation::getOperandsCount() noexcept {
	return operandsCount;
}
double operation::execute(const myVector<double>& operands) {
	double res;
	if (this->getSym() == "+")
		res = operands[1] + operands[0];
	else if (this->getSym() == "-")
		res = operands[1] - operands[0];
	else if (this->getSym() == "~")
		res = -operands[0];
	else if (this->getSym() == "*")
		res = operands[1] * operands[0];
	else if (this->getSym() == "/")
		res = operands[1] / operands[0];
	else if (this->getSym() == "sin")
		res = sin(operands[0]);
	else if (this->getSym() == "cos")
		res = cos(operands[0]);
	else if (this->getSym() == "exp")
		res = exp(operands[0]);
	else if (this->getSym() == "pow")
		res = pow(operands[1], operands[0]);
	else if (this->getSym() == "log")
		res = log(operands[0]);
	else
		throw std::invalid_argument("-1EUnknown operator");
	return res;
}
operation::~operation() {}

operand::operand(const std::string& s, int p) : lexem(s, p) {}
double operand::getValue() noexcept {
	return value;
}
bool operand::isOperation() noexcept {
	return false;
}
operand::~operand() {}

constant::constant(const std::string& s, int p) : operand(s, p) {}
void constant::fillValue() {
	this->value = parser(getSym());
}
constant::~constant() {}

void variable::fillValue() {
	for (size_t i = 0; i < vectorOfVariablesNames.size(); ++i) {
		if (getSym() == vectorOfVariablesNames[i]) {
			value = VectorOfVariablesValues[i];
			return;
		}
	}
}
variable::variable(const std::string& s, int p) : operand(s, p) {}
variable::~variable() {}

myVector<std::string> operation::availableOperations;
myVector<int> operation::priotities;
myVector<int> operation::vOperandsCount;
myVector<bool> operation::vCanBeAfterOperand;
myVector<std::string> variable::vectorOfVariablesNames;
myVector<double> variable::VectorOfVariablesValues;