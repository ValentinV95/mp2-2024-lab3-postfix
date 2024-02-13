#include "arithmetic.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
    cout << "Welcome to the calculator!\n";
    cout << "Please read the following rules before using it:\n";
    cout << "1. You can use four operations: addition (+), subtraction (-), multiplication (*), and division (/).\n";
    cout << "2. Variables can be denoted by letters, digits, and points.\n";
    cout << "3. Spaces are not allowed in expressions.\n";
    cout << "4. Use a point instead of a comma in floating-point numbers.\n";
    cout << "5. Be careful to avoid extra or missing elements.\n";
    cout << endl;

    string expression;
    while (true) {
        try {
            int choice;
            cout << "Enter the arithmetic expression: ";
            getline(cin, expression);
            for (int i = 0; i < expression.length(); i++) {
                if (expression[i] == ' ') {
                    throw invalid_argument("Error: Spaces are not allowed in expressions.");
                }
            }
            TPostfix mathExp(expression);
            cout << "Do you want to calculate?\n";
            cout << "1. Yes\n";
            cout << "2. Enter another expression\n";
            cout << "3. Exit\n";
            cin >> choice;
            cin.ignore(); // Ignore newline character after reading integer input
            if (choice == 1) {
                cout << "Infix form: " << mathExp.getInfix() << "\n";
                mathExp.toPostfix();
                cout << "Postfix form: " << mathExp.getPostfix() << "\n";
                mathExp.calculate();
                cout << "The result: " << mathExp.getResult() << "\n";
            } else if (choice == 2) {
                continue; // Go back to the beginning of the loop to enter another expression
            } else if (choice == 3) {
                break; // Exit the program
            } else {
                cout << "Invalid choice. Please enter a valid option.\n";
            }
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl << endl;
        }
    }

    return 0;
}
