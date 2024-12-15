#include "lexems.h"
#include <gtest.h>
#include <string>

// operation 

TEST(operation, fill_operations) {
	ASSERT_NO_THROW(operation::fillOperations());
}

TEST(operation, is_plus_operation) {
	EXPECT_EQ(true, operation::isOperation("+"));
}

TEST(operation, is_minus_operation) {
	EXPECT_EQ(true, operation::isOperation("-"));
}

TEST(operation, is_multiplication_operation) {
	EXPECT_EQ(true, operation::isOperation("*"));
}

TEST(operation, is_divide_operation) {
	EXPECT_EQ(true, operation::isOperation("/"));
}

TEST(operation, is_left_bracket_operation) {
	EXPECT_EQ(true, operation::isOperation("("));
}

TEST(operation, is_right_bracket_operation) {
	EXPECT_EQ(true, operation::isOperation(")"));
}

TEST(operation, is_unary_minus_operation) {
	EXPECT_EQ(true, operation::isOperation("~"));
}

TEST(operation, is_sin_operation) {
	EXPECT_EQ(true, operation::isOperation("sin"));
}

TEST(operation, is_cos_operation) {
	EXPECT_EQ(true, operation::isOperation("cos"));
}

TEST(operation, is_log_operation) {
	EXPECT_EQ(true, operation::isOperation("log"));
}

TEST(operation, is_pow_operation) {
	EXPECT_EQ(true, operation::isOperation("^"));
}

TEST(operation, is_exp_operation) {
	EXPECT_EQ(true, operation::isOperation("exp"));
}

TEST(operation, can_plus_be_after_operand) {
	EXPECT_EQ(true, operation::canBeAfterOperand("+"));
}

TEST(operation, can_unary_minus_be_after_operand) {
	EXPECT_EQ(false, operation::canBeAfterOperand("~"));
}

TEST(operation, can_left_bracket_be_after_operand) {
	EXPECT_EQ(true, operation::canBeAfterOperand("(")); // false
}

TEST(operation, can_right_bracket_be_after_operand) {
	EXPECT_EQ(true, operation::canBeAfterOperand(")"));
}

TEST(operation, can_pow_be_after_operand) {
	EXPECT_EQ(true, operation::canBeAfterOperand("^"));
}

TEST(operation, can_sin_be_after_operand) {
	EXPECT_EQ(false, operation::canBeAfterOperand("sin"));
}

TEST(operation, is_sin_with_left_bracket_operation) {
	EXPECT_EQ(false, operation::isOperation("sin("));
}

TEST(operation, is_double_unary_minus_operation) {
	EXPECT_EQ(false, operation::isOperation("~~"));
}

TEST(operation, is_s_operation) {
	EXPECT_EQ(false, operation::isOperation("s"));
}

TEST(operation, can_create_operation) {
	ASSERT_NO_THROW(operation("+", 0));
}

TEST(operation, can_get_sym) {
	operation op("sin", 993);
	ASSERT_NO_THROW(op.getSym());
}

TEST(operation, can_get_pos) {
	operation op("sin", 993);
	ASSERT_NO_THROW(op.getPos());
}

TEST(operation, get_sym_is_correct) {
	operation op("sin", 993);
	EXPECT_EQ("sin", op.getSym());
}

TEST(operation, get_pow_is_correct) {
	operation op("sin", 993);
	EXPECT_EQ(993, op.getPos());
}

TEST(operation, is_operation) {
	operation op("+", 0);
	EXPECT_EQ(true, op.isOperation());
}

TEST(operation, can_get_priority) {
	operation op("+", 0);
	ASSERT_NO_THROW(op.getPriority());
}

TEST(operation, get_priority_plus) {
	operation op("+", 0);
	EXPECT_EQ(1, op.getPriority());
}

TEST(operation, get_priority_sin) {
	operation op("sin", 0);
	EXPECT_EQ(3, op.getPriority());
}

TEST(operation, get_priority_left_bracket) {
	operation op("(", 0);
	EXPECT_EQ(0, op.getPriority());
}

TEST(operation, can_get_operand_count) {
	operation op("+", 0);
	ASSERT_NO_THROW(op.getOperandsCount());
}

TEST(operation, get_operand_count_plus) {
	operation op("+", 0);
	EXPECT_EQ(2, op.getOperandsCount());
}

TEST(operation, get_operand_count_sin) {
	operation op("sin", 0);
	EXPECT_EQ(1, op.getOperandsCount());
}

TEST(operation, get_operand_count_left_bracket) {
	operation op("(", 0);
	EXPECT_EQ(0, op.getOperandsCount());
}

TEST(operation, cant_execute_unknown_operator) {
	operation op("%", 0);
	myVector<double> v;
	ASSERT_ANY_THROW(op.execute(v));
}

TEST(operation, cant_execute_unknown_operator_exception) {
	operation op("%", 0);
	myVector<double> v;
	try {
		op.execute(v);
	}
	catch (std::exception& e) {
		EXPECT_EQ("-1EUnknown operator", std::string(e.what()));
	}
}

TEST(operation, cant_execute_with_not_enough_operands) {
	operation op("+", 0);
	myVector<double> v;
	v.push_back(1);
	ASSERT_ANY_THROW(op.execute(v));
}

TEST(operation, cant_execute_with_not_enough_operands_exception) {
	operation op("+", 0);
	myVector<double> v;
	v.push_back(1);
	try {
		op.execute(v);
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L0ENo operand for this operator", std::string(e.what()));
	}
}

static double eps = 1e-10;

TEST(operation, can_execute_plus_operation) {
	operation op("+", 0);
	myVector<double> v;
	v.push_back(1);
	v.push_back(2);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_plus_operation_is_correct) {
	operation op("+", 0);
	myVector<double> v;
	v.push_back(1);
	v.push_back(2);
	EXPECT_EQ(true, abs(op.execute(v) - 3.0) < eps);
}

TEST(operation, can_execute_minus_operation) {
	operation op("-", 0);
	myVector<double> v;
	v.push_back(1);
	v.push_back(2);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_minus_operation_is_correct) {
	operation op("-", 0);
	myVector<double> v;
	v.push_back(1);
	v.push_back(2);
	EXPECT_EQ(true, abs(op.execute(v) - 1.0) < eps);
}

TEST(operation, can_execute_multiplication_operation) {
	operation op("*", 0);
	myVector<double> v;
	v.push_back(1);
	v.push_back(2);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_multiplication_operation_is_correct) {
	operation op("*", 0);
	myVector<double> v;
	v.push_back(1);
	v.push_back(2);
	EXPECT_EQ(true, abs(op.execute(v) - 2.0) < eps);
}

TEST(operation, can_execute_divide_operation) {
	operation op("/", 0);
	myVector<double> v;
	v.push_back(1);
	v.push_back(2);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_divide_operation_is_correct) {
	operation op("/", 0);
	myVector<double> v;
	v.push_back(1);
	v.push_back(2);
	EXPECT_EQ(true, abs(op.execute(v) - 2.0) < eps);
}

TEST(operation, cant_execute_left_bracket_operation) {
	operation op("(", 0);
	myVector<double> v;
	ASSERT_ANY_THROW(op.execute(v));
}

TEST(operation, cant_execute_right_bracket_operation) {
	operation op(")", 0);
	myVector<double> v;
	ASSERT_ANY_THROW(op.execute(v));
}

TEST(operation, can_execute_unary_minus_operation) {
	operation op("~", 0);
	myVector<double> v;
	v.push_back(1);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_unary_minus_operation_is_correct) {
	operation op("~", 0);
	myVector<double> v;
	v.push_back(1);
	EXPECT_EQ(true, abs(op.execute(v) - -1.0) < eps);
}

TEST(operation, can_execute_sin_operation) {
	operation op("sin", 0);
	myVector<double> v;
	v.push_back(1);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_sin_operation_is_correct) {
	operation op("sin", 0);
	myVector<double> v;
	v.push_back(1);
	EXPECT_EQ(true, abs(op.execute(v) - 0.8414709848) < eps);
}

TEST(operation, can_execute_cos_operation) {
	operation op("cos", 0);
	myVector<double> v;
	v.push_back(1);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_cos_operation_is_correct) {
	operation op("cos", 0);
	myVector<double> v;
	v.push_back(1);
	EXPECT_EQ(true, abs(op.execute(v) - 0.5403023059) < eps);
}

TEST(operation, can_execute_log_operation) {
	operation op("log", 0);
	myVector<double> v;
	v.push_back(2);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_log_operation_is_correct) {
	operation op("log", 0);
	myVector<double> v;
	v.push_back(2);
	EXPECT_EQ(true, abs(op.execute(v) - 0.6931471806) < eps);
}

TEST(operation, can_execute_pow_operation) {
	operation op("^", 0);
	myVector<double> v;
	v.push_back(2);
	v.push_back(0.5);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_pow_operation_is_correct) {
	operation op("^", 0);
	myVector<double> v;
	v.push_back(0.5);
	v.push_back(2);
	EXPECT_EQ(true, abs(op.execute(v) - 1.41421356237) < eps);
}

TEST(operation, can_execute_exp_operation) {
	operation op("exp", 0);
	myVector<double> v;
	v.push_back(2);
	ASSERT_NO_THROW(op.execute(v));
}

TEST(operation, execute_exp_operation_is_correct) {
	operation op("exp", 0);
	myVector<double> v;
	v.push_back(2);
	EXPECT_EQ(true, abs(op.execute(v) - 7.389056099) < eps);
}

// 
// operands
//

TEST(constant, can_create_constant) {
	ASSERT_NO_THROW(constant cons("2", 0));
}

TEST(variable, can_create_variable) {
	ASSERT_NO_THROW(variable var("x", 0));
}

TEST(constant, is_constant_operation) {
	constant cons("2", 0);
	EXPECT_EQ(false, cons.isOperation());
}

TEST(variable, is_variable_operation) {
	variable var("x", 0);
	EXPECT_EQ(false, var.isOperation());
}

TEST(constant, can_constant_fill_value) {
	constant cons("2", 0);
	ASSERT_NO_THROW(cons.fillValue());
}

TEST(constant, can_constant_get_value) {
	constant cons("2", 0);
	cons.fillValue();
	ASSERT_NO_THROW(cons.getValue());
}

TEST(constant, is_constant_fill_value_correct) {
	constant cons("2", 0);
	cons.fillValue();
	EXPECT_EQ(true, abs(cons.getValue() - 2.0) < eps);
}

TEST(variable, can_variable_fill_value) {
	variable var("x", 0);
	variable::vectorOfVariablesNames.resize(0);
	variable::VectorOfVariablesValues.resize(0);
	variable::vectorOfVariablesNames.push_back("x");
	variable::VectorOfVariablesValues.push_back(2.0);
	ASSERT_NO_THROW(var.fillValue());
}

TEST(variable, cant_variable_fill_value) {
	variable var("x", 0);
	variable::vectorOfVariablesNames.resize(0);
	variable::VectorOfVariablesValues.resize(0);
	variable::vectorOfVariablesNames.push_back("y");
	variable::VectorOfVariablesValues.push_back(2.0);
	ASSERT_ANY_THROW(var.fillValue());
}

TEST(variable, cant_variable_fill_value_exception) {
	variable var("x", 0);
	variable::vectorOfVariablesNames.resize(0);
	variable::VectorOfVariablesValues.resize(0);
	variable::vectorOfVariablesNames.push_back("y");
	variable::VectorOfVariablesValues.push_back(2.0);
	try {
		var.fillValue();
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L0ENo value to fill", std::string(e.what()));
	}
}

TEST(variable, can_variable_get_value) {
	variable var("x", 0);
	variable::vectorOfVariablesNames.resize(0);
	variable::VectorOfVariablesValues.resize(0);
	variable::vectorOfVariablesNames.push_back("x");
	variable::VectorOfVariablesValues.push_back(2.0);
	var.fillValue();
	ASSERT_NO_THROW(var.getValue());
}

TEST(variable, variable_get_value_correct) {
	variable var("x", 0);
	variable::vectorOfVariablesNames.resize(0);
	variable::VectorOfVariablesValues.resize(0);
	variable::vectorOfVariablesNames.push_back("x");
	variable::VectorOfVariablesValues.push_back(2.0);
	var.fillValue();
	EXPECT_EQ(true, abs(var.getValue() - 2.0) < eps);
}