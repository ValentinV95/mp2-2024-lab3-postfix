//тесты самописного дерева классов лексем
#include "gtest.h"
#include "lexem.h"


TEST(lexem, can_create_lexem)
{
	ASSERT_NO_THROW(lexem d("",2));
}
TEST(lexem, can_isOperation_lexem_correct)
{
	lexem d("", 2);
	ASSERT_NO_THROW(d.isOperation());
	ASSERT_EQ(d.isOperation(), false);
}
TEST(lexem, can_GetLexemID_lexem_correct)
{
	lexem d("", 2);
	ASSERT_NO_THROW(d.Get_Lexem_ID());
	ASSERT_EQ(d.Get_Lexem_ID(), false);
}
TEST(lexem, can_GetPos_lexem_correct)
{
	lexem d("", 2);
	ASSERT_NO_THROW(d.GetPos());
	ASSERT_EQ(d.GetPos(), 2);
}
TEST(lexem, can_Get_VAL_NAME_lexem_correct)
{
	lexem d("abcdefg", 2);
	ASSERT_NO_THROW(d.Get_VAL_NAME());
	ASSERT_EQ(d.Get_VAL_NAME(), "abcdefg");
}








TEST(operand, can_create_operand)
{
	ASSERT_NO_THROW(operand d("", 2, 12.4));
}
TEST(operand, can_getValue_operand_correct)
{
	operand d("", 2, 12.4);
	ASSERT_NO_THROW(d.getValue());
	ASSERT_EQ(12.4, d.getValue());
}
TEST(operand, can_setValue_operand_correct)
{
	operand d("", 2, 12.4);
	ASSERT_NO_THROW(d.setValue_(84.1221));
	ASSERT_EQ(84.1221, d.getValue());
}
TEST(operand, is_constanta_false_operand)
{
	operand d("", 2, 12.4);
	ASSERT_NO_THROW(d.isConstanta());
	ASSERT_EQ(false, d.isConstanta());
}
TEST(operand, is_operation_false_operand)
{
	operand d("", 2, 12.4);
	ASSERT_NO_THROW(d.isOperation());
	ASSERT_EQ(false, d.isOperation());
}
TEST(operand, is_function_false_operand)
{
	operand d("", 2, 12.4);
	ASSERT_NO_THROW(d.isFunction());
	ASSERT_EQ(false, d.isFunction());
}
TEST(operand, can_get_correct_ID_operand)
{
	operand d("", 2, 12.4);
	ASSERT_NO_THROW(d.Get_Lexem_ID());
	ASSERT_EQ(-1, d.Get_Lexem_ID());
}
TEST(operand, can_get_correct_val_name_operand)
{
	operand d("abcabcd", 2, 12.4);
	ASSERT_NO_THROW(d.Get_VAL_NAME());
	ASSERT_EQ("abcabcd", d.Get_VAL_NAME());
}








TEST(operation, can_create_operation)
{
	ASSERT_NO_THROW(operation d("", 2, 4, false, false));
}
TEST(operation, can_is_utility_operation_true)
{
	operation d("", 2, 4, false, true);
	ASSERT_NO_THROW(d.isUtility());
	ASSERT_EQ(d.isUtility(),true);
}
TEST(operation, can_is_utility_operation_false)
{
	operation d("", 2, 4, true, false);
	ASSERT_NO_THROW(d.isUtility());
	ASSERT_EQ(d.isUtility(), false);
}
TEST(operation, can_is_unar_operation_true)
{
	operation d("", 2, 4, true, false);
	ASSERT_NO_THROW(d.isUnar());
	ASSERT_EQ(d.isUnar(), true);
}
TEST(operation, can_is_unar_operation_false)
{
	operation d("", 2, 4, false, true);
	ASSERT_NO_THROW(d.isUnar());
	ASSERT_EQ(d.isUnar(), false);
}
TEST(operation, correct_get_priority_operation)
{
	operation d("", 2, 23, false, false);
	ASSERT_NO_THROW(d.getPriotiry());
	ASSERT_EQ(d.getPriotiry(), 23);
}
TEST(operation, correct_get_ID_operation)
{
	operation d("", 2, 23, false, false,342);
	ASSERT_NO_THROW(d.Get_Lexem_ID());
	ASSERT_EQ(d.Get_Lexem_ID(), 342);
}
TEST(operation, correct_get_value_name_operation)
{
	operation d("oper", 2, 23, false, false, 342);
	ASSERT_NO_THROW(d.Get_VAL_NAME());
	ASSERT_EQ(d.Get_VAL_NAME(), "oper");
}
TEST(operation, cant_GetValue_operation)
{
	operation d("oper", 2, 23, false, false, 342);
	ASSERT_ANY_THROW(d.getValue());
}
TEST(operation, cant_SetValue_operation)
{
	operation d("oper", 2, 23, false, false, 342);
	ASSERT_ANY_THROW(d.setValue_(23));
}
TEST(operation, get_correct_pos_operation)
{
	operation d("oper", 2, 23, false, false);
	ASSERT_NO_THROW(d.GetPos());
	ASSERT_EQ(d.GetPos(), 2);
}
TEST(operation, correct_ID_plus_operation)
{
	operation d("+", 2, 23, false, false);
	ASSERT_EQ(d.Get_Lexem_ID(), -5);
}
TEST(operation, correct_ID_mult_operation)
{
	operation d("*", 2, 23, false, false);
	ASSERT_EQ(d.Get_Lexem_ID(), 6);
}
TEST(operation, correct_ID_div_operation)
{
	operation d("/", 2, 23, false, false);
	ASSERT_EQ(d.Get_Lexem_ID(), -6);
}
TEST(operation, correct_ID_sub_un_operation)
{
	operation d("-", 2, 23, true, false);
	ASSERT_EQ(d.Get_Lexem_ID(), -2);
}
TEST(operation, correct_ID_sub_operation)
{
	operation d("-", 2, 23, false, false);
	ASSERT_EQ(d.Get_Lexem_ID(), 5);
}
TEST(operation, correct_ID_op_br_operation)
{
	operation d("(", 2, 23, false, true);
	ASSERT_EQ(d.Get_Lexem_ID(), 7);
}
TEST(operation, correct_ID_cl_br_operation)
{
	operation d(")", 2, 23, false, true);
	ASSERT_EQ(d.Get_Lexem_ID(), -7);
}
TEST(operation, is_operation_true)
{
	operation d("", 2, 23, false, true);
	ASSERT_NO_THROW(d.isOperation());
	ASSERT_EQ(d.isOperation(), true);
}






TEST(constant, can_create) {
	constant d("", 2, 23.32);
}
TEST(constant, can_get_correct_ID) {
	constant d("", 2, 23.32);
	ASSERT_NO_THROW(d.Get_Lexem_ID());
	ASSERT_EQ(d.Get_Lexem_ID(), 1);
}
TEST(constant, can_get_correct_pos) {
	constant d("", 2, 23.32);
	ASSERT_NO_THROW(d.GetPos());
	ASSERT_EQ(d.GetPos(), 2);
}
TEST(constant, can_get_correct_value) {
	constant d("", 2, 23.32);
	ASSERT_NO_THROW(d.getValue());
	ASSERT_EQ(d.getValue(),23.32);
}
TEST(constant, can_get_correct_value_name) {
	constant d("asd", 2, 23.32);
	ASSERT_NO_THROW(d.Get_VAL_NAME());
	ASSERT_EQ(d.Get_VAL_NAME(), "asd");
}
TEST(constant, can_set_correct_value) {
	constant d("", 2, 23.32);
	ASSERT_NO_THROW(d.setValue_(34.5));
	ASSERT_EQ(d.getValue(), 34.5);
}
TEST(constant, is_constanta_true) {
	constant d("", 2, 23.32);
	ASSERT_NO_THROW(d.isConstanta());
	ASSERT_EQ(d.isConstanta(), true);
}
TEST(constant, false_is_function) {
	constant d("", 2, 23.32);
	ASSERT_NO_THROW(d.isFunction());
	ASSERT_EQ(d.isFunction(), false);
}
TEST(constant, false_is_operation) {
	constant d("", 2, 23.32);
	ASSERT_NO_THROW(d.isOperation());
	ASSERT_EQ(d.isOperation(), false);
}






TEST(variable, can_create) {
	ASSERT_NO_THROW(variable d("", 2, 0.0));
}
TEST(variable, can_get_correct_ID) {
	variable d("", 2, 0.0);
	ASSERT_NO_THROW(d.Get_Lexem_ID());
	ASSERT_EQ(d.Get_Lexem_ID(), 2);
}
TEST(variable, is_operation_false) {
	variable d("", 2, 0.0);
	ASSERT_NO_THROW(d.isOperation());
	ASSERT_EQ(d.isOperation(), false);
}
TEST(variable, is_func_false) {
	variable d("", 2, 0.0);
	ASSERT_NO_THROW(d.isFunction());
	ASSERT_EQ(d.isFunction(), false);
}
TEST(variable, is_func_true) {
	variable d("", 2, 0.0,true);
	ASSERT_NO_THROW(d.isFunction());
	ASSERT_EQ(d.isFunction(), true);
}
TEST(variable, can_get_value_correct) {
	variable d("", 2, 23.2);
	ASSERT_NO_THROW(d.getValue());
	ASSERT_EQ(d.getValue(),23.2 );
}
TEST(variable, can_set_value_correct) {
	variable d("", 2, 23.2);
	ASSERT_NO_THROW(d.setValue_(34.1));
	ASSERT_EQ(d.getValue(), 34.1);
}
TEST(variable, get_value_name) {
	variable d("uwu", 2, 23.2);
	ASSERT_NO_THROW(d.Get_VAL_NAME());
	ASSERT_EQ(d.Get_VAL_NAME(), "uwu");
}
TEST(variable, ID_funcs_sin) {
	variable d("sin", 2, 23.2,true);
	ASSERT_EQ(d.Get_Lexem_ID(),3 );
}
TEST(variable, ID_funcs_cos) {
	variable d("cos", 2, 23.2, true);
	ASSERT_EQ(d.Get_Lexem_ID(), -3);
}
TEST(variable, ID_funcs_tan) {
	variable d("tan", 2, 23.2, true);
	ASSERT_EQ(d.Get_Lexem_ID(), 4);
}
TEST(variable, ID_funcs_cot) {
	variable d("cot", 2, 23.2, true);
	ASSERT_EQ(d.Get_Lexem_ID(), -4);
}
TEST(variable, false_is_constanta) {
	variable d("sth", 2, 23.2, true);
	ASSERT_NO_THROW(d.isConstanta());
	ASSERT_EQ(d.isConstanta(), false);
}