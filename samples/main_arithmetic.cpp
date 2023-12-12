// реализация пользовательского приложения
#include "arithmetic.h"

int main()
{
    cout << "Welcome to calculate!\n"<<
           "You can use unar minus, +, -, *, / , (, ), sin(), cos(), tg(), exp(), lg(). YOU CAN'T USE SPACES!\n"<<
           "So, you can give me as much as you want variables, but it should be like xNUM, where NUM is num (1,2,3...) (x1). Then you should give me their value\n"<<
           "Good luck!" << endl;
    cout << "Enter the equation:" << endl;
    string equation;
    double result;
    cin >> equation;
    Arithmetic res (equation);
    //cout << "Enter the values of variables: " << endl;  //ПРОВЕРИТЬ МАПУ НА ПУСТОТУ И В ЭТОМ СЛУЧАЕ ЭТО
    res.GetVars();
    result = res.Calculate();
    cout << result << endl;
    while (true){
        char choice;
        cout << "Do you want to change the parameters and recalculate the equation? Y/N: ";
        cin >> choice;
        if (choice == 'N' || choice=='n'){
            break;
        }
        else if (choice!='Y' && choice!='y'){
            break;
        }
        //cout << "Enter the values of variables: " << endl;
        res.GetVars();
        result = res.Calculate();
        cout << result << endl;
    }

}
