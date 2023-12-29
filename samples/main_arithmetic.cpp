#include <iostream>
#include "arithmetic.h"

int main()
{
    int main()
{
    cout << "Hello, before you will use this calculator, you should read some rules: \n";
    cout << "You can use 4 operations: addition +, subsrtaction -, multiplication *, division / \n";
    cout << "You can denote vars by letters, digits and points \n";
    cout << "You can't use spaces in expression \n";
    cout << "You should put a point instead of a comma in floating point numbers \n";
    cout << "You should avoid extra or misssing elements, be careful \n ";
    cout << endl;
    string expression;
    cout << "Enter the arifmetic expression: \n";
    cin >> expression;
    while (true)
    {
        try
        {
            int choice;
            cout << "Do you want to calculate? \n";
            cout << "1. Yes \n";
            cout << "2. Again \n";
            cout << "3. No \n";
            cin >> choice;
            if (choice == 1)
            {
                TPostfix mathexp(expression);
                cout << "Infix form: " << mathexp.getInfix() << "\n";
                mathexp.toPostfix();
                cout << "Postfix form: " << mathexp.getPostfix() << "\n";
                mathexp.calculate();
                cout << "The result: " << mathexp.getResult() << "\n";
            }
            if (choice == 2)
            {
                cout << "Enter the arifmetic expression: \n";
                cin >> expression;
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
}

