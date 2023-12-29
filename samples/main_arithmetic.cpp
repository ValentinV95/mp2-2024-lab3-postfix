#include <iostream>
#include "arithmetic.h"

int main()
{
    cout << "Hello, before you will use this calculator, you should read some rules: \n";
    cout << "You can use 4 operations: addition +, subsrtaction -, multiplication *, division / \n";
    cout << "You can denote vars by letters, digits and points \n";
    cout << "You can't use spaces in expression \n";
    cout << "You should put a point instead of a comma in floating point numbers \n";
    cout << "You should avoid extra or misssing elements, be careful \n ";
    cout << endl;
    cout << "Enter the arifmetic expression: \n";
    string expression;
    string error = "";
    while (true)
    {
        try
        {
            int choice;
            cout << "Enter the arifmetic expression: \n";
            getline(cin, expression);
            for (int i = 0; i < expression.length(); i++)
            {
                error += expression[i];
                if (expression[i] == ' ')
                {
                    error += " <- You shouldn`t use spaces";
                    throw invalid_argument(error.c_str());
                }
            }
            TPostfix mathexp(expression);
            cout << "Do you want to calculate? \n";
            cout << "1. Yes \n";
            cout << "2. Again \n";
            cout << "3. No \n";
            cin >> choice;
            if (choice == 1)
            {
                cout << "Infix form: " << mathexp.getInfix() << "\n";
                mathexp.toPostfix();
                cout << "Postfix form: " << mathexp.getPostfix() << "\n";
                mathexp.calculate();
                cout << "The result: " << mathexp.getResult() << "\n";
                cout << "Do you want to calculate? \n";
                cout << "2. Again \n";
                cout << "3. No \n";
                cin >> choice;
            }
            if (choice == 2)
            {
                cout << "Enter the arifmetic expression: \n";
                getline(cin, expression);
                continue;
            }
            if (choice == 3)
            {
                break;
            }
        }
        catch (exception& e)
        {
            cout << e.what() << endl << endl;
        }
    }
    return 0;
}

