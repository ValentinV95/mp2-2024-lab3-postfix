// реализация пользовательского приложения
  #include <iostream>
#include <string.h>
#include "stack.h"
#include "arithmetic.h"
using namespace std;


int main() {
    string h;
    cout << "enter the expression";
    cin >> h;
    TCalculator s(h);
    cout << s.Calc();
    return 0;
}
};

