#include <gtest.h>
#include "lexem.h"

TEST(operation, can_be_created)
{
	ASSERT_NO_THROW(operation a);
}

TEST(operation, is_statement)
{
	operation a;
	EXPECT_TRUE(a.IsStmt());
}

TEST(operation, can_be_created_with_id)
{
	ASSERT_NO_THROW(operation a(4));
}

TEST(operation, throws_when_created_with_inappropriate_id)
{
	ASSERT_ANY_THROW(operation a(-1));
	ASSERT_ANY_THROW(operation b(30));
}

TEST(operation, can_get_its_fields)
{
	operation a(10);
	EXPECT_EQ(10, a.GetId());
	EXPECT_EQ(6, a.GetPriority());
	EXPECT_EQ(1, a.GetArity());
	EXPECT_EQ("sin", a.GetName());
}

TEST(operation, getting_name_from_default_constructed_throws)
{
	operation a;
	ASSERT_ANY_THROW(a.GetName());
}

TEST(operation, can_be_copied)
{
	operation a(4);
	ASSERT_NO_THROW(operation b(a));
}

TEST(operation, copied_equals_to_source)
{
	operation a(4), b(a);
	EXPECT_EQ(a.GetPriority(), b.GetPriority());
	EXPECT_EQ(a.GetId(), b.GetId());
	EXPECT_EQ(a.GetArity(), b.GetArity());
}

TEST(operation, can_identify_operation_by_string)
{
	size_t id;
	ASSERT_NO_THROW(id = operation::StmtId("acos"));
	EXPECT_EQ(15, id);
}

TEST(operation, indicates_when_string_is_not_an_operation)
{
	size_t id;
	id = operation::StmtId("ceil");
	EXPECT_EQ(-1, id);
}

TEST(operation, can_be_printed)
{
	operation A(4);
	stringstream iostr;
	string s;
	ASSERT_NO_THROW(iostr << A);
	iostr >> s;
	EXPECT_EQ("*", s);
}

 //Don't now if folowing Test needed:
TEST(operation, pointer_can_be_assigned_to_base_class_pointer)
{
	lexem* A;
	operation* B = new operation(2);
	ASSERT_NO_THROW(A = B);
	delete B;
}

TEST(operation, being_assigned_to_basic_class_pointer_can_be_casted_to_itself)
{
	operation* B = new operation(2),* C;
	lexem* A = B;
	ASSERT_NO_THROW(C = dynamic_cast<operation*>(A));
	EXPECT_EQ(B->GetId(), C->GetId());
	EXPECT_EQ(B->GetArity(), C->GetArity());
	EXPECT_EQ(B->GetPriority(), C->GetPriority());
	delete B;
}

TEST(operation, methods_can_be_called_from_base_class)
{
	lexem* A;
	operation* B = new operation(8);
	A = B;
	stringstream iostr;
	string s;
	bool f;
	ASSERT_NO_THROW(f = A->IsStmt());
	EXPECT_EQ(B->IsStmt(), f);
	ASSERT_NO_THROW(iostr << *A);
	iostr >> s;
	EXPECT_EQ(B->GetName(), s);
	delete B;
}







TEST(constant, can_be_created)
{
	ASSERT_NO_THROW(constant A);
}

TEST(constant, is_not_statement)
{
	constant A;
	EXPECT_EQ(false, A.IsStmt());
}

TEST(constant, is_constant)
{
	constant A;
	EXPECT_EQ(true, A.IsConst());
}

TEST(constant, can_be_created_from_double)
{
	ASSERT_NO_THROW(constant A(2.5));
}

TEST(constant, can_get_value)
{
	constant A(2.5);
	ASSERT_NO_THROW(A.GetVal());
	EXPECT_DOUBLE_EQ(2.5, A.GetVal());
}

TEST(constant, can_be_printed)
{
	constant A(2.5);
	stringstream iostr;
	double a, b=2.5;
	ASSERT_NO_THROW(iostr << A);
	iostr >> a;
	EXPECT_DOUBLE_EQ(b, a);
}

TEST(constant, can_be_copied)
{
	constant A(2.5);
	ASSERT_NO_THROW(constant B(A));
}

TEST(constant, copied_equals_to_source)
{
	constant A(2.5), B(A);
	EXPECT_EQ(A.GetVal(), B.GetVal());
}

TEST(constant, methods_can_be_called_from_base_classes)
{
	lexem* L;
	operand* O;
	constant* C = new constant(2.5);
	L = O = C;
	stringstream iostr;
	double d;
	bool f;
	ASSERT_NO_THROW(f = L->IsStmt());
	EXPECT_EQ(false, f);
	ASSERT_NO_THROW(iostr << *L);
	iostr >> d;
	EXPECT_DOUBLE_EQ(2.5, d);
	ASSERT_NO_THROW(f = O->IsStmt());
	EXPECT_EQ(false, f);
	ASSERT_NO_THROW(iostr << *O);
	iostr >> d;
	EXPECT_DOUBLE_EQ(2.5, d);
	ASSERT_NO_THROW(f = O->IsConst());
	EXPECT_EQ(true, f);
	ASSERT_NO_THROW(d = O->GetVal());
	EXPECT_DOUBLE_EQ(2.5, d);
	delete C;
}







TEST(variable, can_be_created)
{
	ASSERT_NO_THROW(variable A);
}

TEST(variable, is_not_statement)
{
	variable A;
	EXPECT_EQ(false, A.IsStmt());
}

TEST(variable, is_not_constant)
{
	variable A;
	EXPECT_EQ(false, A.IsConst());
}

TEST(variable, can_be_created_from_string)
{
	ASSERT_NO_THROW(variable A("force"));
	variable::GetValVec().clear();			// Need to clear variables after each test since
	variable::GetNameVec().clear();			// they do not consider to be different programms
}

TEST(variable, can_be_initiated)
{
	variable A("force");
	Vec<double> *v = &(variable::GetValVec());
	variable::Init(2, 4.5);
	EXPECT_DOUBLE_EQ(4.5, v->operator[](2));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, can_get_value_and_name)
{
	variable A("force");
	string s;
	double d;
	ASSERT_NO_THROW(A.GetId());
	EXPECT_EQ(2, A.GetId());
	variable::Init(2, 4.5);
	ASSERT_NO_THROW(d = A.GetVal());
	EXPECT_DOUBLE_EQ(4.5, d);
	ASSERT_NO_THROW(s = A.GetName());
	EXPECT_EQ("force", s);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, creating_variable_with_new_name_adds_new_cell)
{
	variable A("force");
	EXPECT_EQ(3, variable::GetNameVec().GetSize());
	variable B("square");
	EXPECT_EQ(4, variable::GetNameVec().GetSize());
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, creating_variable_with_existing_name_does_not_add_new_cell)
{
	variable A("force");
	EXPECT_EQ(3, variable::GetNameVec().GetSize());
	variable B("force");
	EXPECT_EQ(3, variable::GetNameVec().GetSize());
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, has_pi_and_e_constants_upon_creation)
{
	variable A;
	EXPECT_EQ(2, variable::GetNameVec().GetSize());
	variable B("pi");
	EXPECT_EQ(2, variable::GetNameVec().GetSize());
	EXPECT_DOUBLE_EQ(acos(-1.0), B.GetVal());
	variable C("e");
	EXPECT_EQ(2, variable::GetNameVec().GetSize());
	EXPECT_DOUBLE_EQ(exp(1.0), C.GetVal());
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, can_be_copied)
{
	variable A("force");
	ASSERT_NO_THROW(variable B(A));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, copied_equals_to_source)
{
	variable A("force"), B(A);
	EXPECT_EQ(A.GetId(), B.GetId());
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, copying_value_does_not_add_new_cell)
{
	variable A("force");
	EXPECT_EQ(3, variable::GetNameVec().GetSize());
	variable B(A);
	EXPECT_EQ(A.GetId(), B.GetId());
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, has_limit)
{
	for (size_t i = 0; i < 1026; i++)
	{
		variable::GetNameVec().push_back("__" + to_string(i));
		variable::GetValVec().push_back(0.0);
	}
	EXPECT_EQ(1026, variable::GetNameVec().GetSize());
	ASSERT_ANY_THROW(variable A("fubar"));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, can_be_printed)
{
	variable A("force");
	stringstream iostr;
	string s;
	ASSERT_NO_THROW(iostr << A);
	iostr >> s;
	EXPECT_EQ("force", s);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(variable, methods_can_be_called_from_base_classes)
{
	lexem* L;
	operand* O;
	variable* V = new variable("force");
	variable::Init(2, 4.5);
	L = O = V;
	stringstream iostr;
	string s;
	double d;
	bool f;
	ASSERT_NO_THROW(f = L->IsStmt());
	EXPECT_EQ(false, f);
	ASSERT_NO_THROW(iostr << *L);
	iostr >> s;
	EXPECT_EQ("force", s);
	ASSERT_NO_THROW(f = O->IsStmt());
	EXPECT_EQ(false, f);
	ASSERT_NO_THROW(iostr << *O);
	iostr >> s;
	EXPECT_EQ("force", s);
	ASSERT_NO_THROW(f = O->IsConst());
	EXPECT_EQ(false, f);
	ASSERT_NO_THROW(d = O->GetVal());
	EXPECT_DOUBLE_EQ(4.5, d);
	delete V;
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}