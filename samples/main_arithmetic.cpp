#include <iostream>
#include "arithmetic.h"

int main()
{
    cout << "Hello, before you will use this calculator, you should read some rules: \n";
    cout << "You can use 4 operations: addition +, subsrtaction -, multiplication *, division / \n";
    cout << "Don't use spaces in your line \n";
    cout << "You can denote vars by letters, digits and points \n";
    cout << "You should put a point instead of a comma in floating point numbers \n";
    cout << "You should avoid extra or misssing elements, be careful \n ";
    cout << endl;
    string line;
    cout << "Enter the arifmetic expression: \n";
    cin >> line;
    string error;
    while (true)
    {
        try
        {
            for (int i = 0; i < line.size(); i++)
            {
                error += line[i];
                if (line[i] == ' ')
                {
                    error += "Don't forget, you can't use spaces in your line";
                    throw invalid_argument(error.c_str());
                }
            }
            int choice;
            cout << "Do you want to calculate? \n";
            cout << "1. Yes \n";
            cout << "2. No \n";
            cin >> choice;
            if (choice == 1)
            {
                TPostfix mathexp(line);
                double res = mathexp.calculate();
                cout << "The result: " << res << "\n";
                cout << "Do you want to calculate? \n";
                cout << "1. Yes \n";
                cout << "2. No \n";
            }
            if (choice == 2)
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

