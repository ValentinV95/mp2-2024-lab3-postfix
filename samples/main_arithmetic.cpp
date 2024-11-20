// реализация пользовательского приложения
#include "stack.h"
#include <iostream>

using namespace std;

void Foo() {
	myStack<int> st;

	for (int i = 0; i < 1000; ++i) st.push(i);
}

int main()
{
	myStack<int> st;
	st.push(1);
	st.push(2);
	st.push(123);
	myStack<int> st2;
	st2 = st;
//	st2.clear();

	for (int i = 0; i < 1000000; ++i) {
		Foo();
		cout << i << endl;
	}
	int a;
	cin >> a;
	return 0;
}
