// объявление функций и классов для вычисления арифметических выражений

#include "stack.h"
#include <vector>
#include <map>
#include <string>

using namespace std;
class Arithmetic{
private:
    string infix;
    vector<string> postfix;
    vector<string> lexems;
    DStack<string> stack;
    map <string, double>  var;

    void Parse();
    void toPostfix();
public:
    Arithmetic(string infix);
    ~Arithmetic();
    int InfixCheck();
    string GetInfix() const;
    void GetVars();
    vector<string> GetPostfix() const;
    double StringToDouble(string str);
    vector<string>GetLexems() const;
    double Calculate();
};


