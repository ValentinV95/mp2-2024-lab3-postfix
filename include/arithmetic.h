// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include <vector>
#include <map>
using namespace std;
class ArithmeticExpr {
	string infix;
	string pubpostfix;
	vector<string> postfix;
	vector<string> lexems;
	map<string, double> operands;
	string priorStr[12] = {"(","+","-","*","/","~","sin","cos","tg","ctg","ln","exp"}; 
	int priorVal[12]= { 0,1,1,2,2,3,4,4,4,4,4,4 };
public:
	ArithmeticExpr(string infx);
	void Parse();
	void ToPostfix();
	string GetInfix()const;
	string GetPostfix() const;
	vector <string> GetLexems() const;
	vector<string> GetOperands() const;
	double Calculate(const map<string, double>& value);
	string isNumberOrVar(string infx); // selects a substring from the zero character from the string, if it is a number or a variable
	double Translate(string snum);
	string isFunc(string infx); //selects a substring from a string with a null character if it is a function
	int Priority(string item);
};
int StringIsAlmostCorrect(string s);  //eliminates most of the errors from the user needed to simplify the subsequent code