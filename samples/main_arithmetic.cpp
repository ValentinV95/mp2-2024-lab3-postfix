// реализация пользовательского приложения
#include "arithmetic.h"
#include <map>
#include <string>
using namespace std;
int main()
{

    setlocale(LC_ALL, "Russian");
    string exprstr;
    cout << "Entry rules: "<<endl;
    cout << "Enter an expression without spaces" << endl; 
    cout << "All variables have the form x*, where* is any number; " << endl;
    cout << "The expression itself can contain only numbers, variables specified by the rule, and functions (sin(), cos(), tg(), ctg(), ln(), exp())" << endl;
    cout << "All operations are separated by parentheses, that is, an expression of the form 5+-4 is not allowed" << endl;
    int fl;
    do {
        fl = 1;     
        try {
            cout << "Enter a correct expression" << endl;
            cin >> exprstr;
            ArithmeticExpr expr(exprstr);
            expr.ToPostfix();
            vector<string> operands = expr.GetOperands();
            map<string, double> values;
            double val;
            for (const auto& op : operands) {
                if (op[0] == 'x') {
                    cout << "Enter a value " << op << ": ";
                    cin >> val;
                    values[op] = val;
                }
            }
            cout << "The resulting infix form is: " << expr.GetInfix() << endl;
            cout << "The resulting postfix form is: " << expr.GetPostfix() << endl;
            cout << "Result of calculation is: " << expr.Calculate(values) << endl;
            fl = 0;
        }
        catch (const exception& e) {
            cout << "The entered string is incorrect" << endl;
            cout << e.what() << endl;
            cout << "Remark: " << endl;
            cout << "If the error is in the '-1' character, it means that the expression ends with an operation or an opening parenthesis" << endl;
            cout << "If the error is in the '-2' character, it means that the number of openingand closing brackets is not equal" << endl;

        }
    } while (fl);
    
}
