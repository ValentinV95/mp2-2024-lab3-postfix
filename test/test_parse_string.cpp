#include "parse_string.h"
#include "gtest.h"

TEST(parse_string, _1_) {

	vector<lexem*> v1 = { new lexem("1",0),new lexem("+",0),new lexem("2",0) },v2;
	v2 = Main_Parser("1+2");
	bool f = v1.size()==v2.size();
	
	for (int i = 0; i < v1.size(); i++) {
		f *= (v1[i]->Get_VAL_NAME() == v2[i]->Get_VAL_NAME());
	}
	ASSERT_EQ(f, true);
}
TEST(parse_string, _2_) {

	vector<lexem*> v1 = { new lexem("1",0),new lexem("+",0),new lexem("2",0) }, v2;
	v2 = Main_Parser("   1 +      2");
	bool f = v1.size() == v2.size();

	for (int i = 0; i < v1.size(); i++) {
		f *= (v1[i]->Get_VAL_NAME() == v2[i]->Get_VAL_NAME());
	}
	ASSERT_EQ(f, true);
}
TEST(parse_string, _3_) {

	vector<lexem*> v1 = { new lexem("(",0),new lexem("-1",0),new lexem(")",0),new lexem("*",0),new lexem("1",0),new lexem("+",0),new lexem("(",0),new lexem("-1",0),new lexem(")",0),new lexem("*",0),new lexem("2",0) }, v2;
	v2 = Main_Parser("-1+-2");
	bool f = v1.size() == v2.size();

	for (int i = 0; i < v1.size(); i++) {
		f *= (v1[i]->Get_VAL_NAME() == v2[i]->Get_VAL_NAME());
	}
	ASSERT_EQ(f, true);
}
TEST(parse_string, _4_) {

	vector<lexem*> v1 = { new lexem("2.3e-2",0),new lexem("/",0),new lexem("(",0),new lexem("-1",0),new lexem(")",0),new lexem("/",0),new lexem("4",0),new lexem("*",0),new lexem("(",0),new lexem("43",0),new lexem(")",0) }, v2;
	
	v2 = Main_Parser("2.3e-2/-4(43)");
	bool f = v1.size() == v2.size();

	for (int i = 0; i < v1.size(); i++) {
		f *= (v1[i]->Get_VAL_NAME() == v2[i]->Get_VAL_NAME());
	}
	ASSERT_EQ(f, true);
}
TEST(parse_string, err_bracket_no_open) {
	ASSERT_ANY_THROW(Main_Parser("2(3)-45)"));
}
TEST(parse_string, err_bracket_no_close) {
	ASSERT_ANY_THROW(Main_Parser("(2(3)-45"));
}
TEST(parse_string, err_bracket_rev) {
	ASSERT_ANY_THROW(Main_Parser(")32("));
}
TEST(parse_string, err_bracket_empty) {
	ASSERT_ANY_THROW(Main_Parser("(3+2)()"));
}
TEST(parse_string, inc_sym_at_the_end) {
	ASSERT_ANY_THROW(Main_Parser("(3+2)+"));
}
TEST(parse_string, _sym_at_the_end) {
	ASSERT_NO_THROW(Main_Parser("(3+2)5"));
}
TEST(parse_string, inc_sym) {
	ASSERT_ANY_THROW(Main_Parser("(3+#)"));
}
TEST(parse_string, inc_points_doubled) {
	ASSERT_ANY_THROW(Main_Parser("(3+3.3.3)"));
}
TEST(parse_string, inc_points) {
	ASSERT_ANY_THROW(Main_Parser("(3+3.)"));
}
TEST(parse_string, cor_points) {
	ASSERT_NO_THROW(Main_Parser("(3+.3)"));
}
TEST(parse_string, non_unar_doubled_operations_p) {
	ASSERT_ANY_THROW(Main_Parser("(3++3)"));
}
TEST(parse_string, non_unar_doubled_operations_m) {
	ASSERT_ANY_THROW(Main_Parser("(3+*3)"));
}
TEST(parse_string, non_unar_doubled_operations_d) {
	ASSERT_ANY_THROW(Main_Parser("(3+/3)"));
}
TEST(parse_string, unar_doubled_operations) {
	ASSERT_NO_THROW(Main_Parser("(3+-3)"));
}
TEST(parse_string, const_aft_const_work) {
	ASSERT_NO_THROW(Main_Parser("3 3 3 4"));
}
TEST(parse_string, br_after_func_work1) {
	ASSERT_NO_THROW(Main_Parser("sin(3 3 4)"));
}
TEST(parse_string, br_after_func_work2) {
	ASSERT_NO_THROW(Main_Parser("sin       (3 3 4)"));
}
TEST(parse_string, br_after_func_work3) {
	ASSERT_NO_THROW(Main_Parser("cos (sin       (3 3 4))"));
}
TEST(parse_string, emp_br_with_space) {
	ASSERT_ANY_THROW(Main_Parser("cos (          )"));
}
TEST(parse_string, cant_point_in_vars1) {
	ASSERT_ANY_THROW(Main_Parser("3 + 4 - a.32"));
}
TEST(parse_string, cant_point_in_vars2) {
	ASSERT_ANY_THROW(Main_Parser("3 + 4 - .a32"));
}
TEST(parse_string, point) {
	ASSERT_ANY_THROW(Main_Parser("(.)"));
}
TEST(parse_string, cant_start_with_non_unar) {
	ASSERT_ANY_THROW(Main_Parser("+(3+4)"));
}
TEST(parse_string, can_start_with_unar) {
	ASSERT_NO_THROW(Main_Parser("-(3+4)"));
}