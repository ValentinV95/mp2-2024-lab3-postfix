// реализация пользовательского приложения
#include "stack.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	TStack<string> a;
	string text = "Amogus";
	for (size_t i = 0; i < 100; i++) {
		a.push(text);
	}
	cout << a.top() << endl;
	for (size_t i = 0; i < 100; i++) {
		cout << a.pop() << ' ';
	}
	return 0;
}
