#include <iostream>
#include"Table.h"
#include "Poliz.h"
#include "Arithmetik.h"	
#include <locale>
using namespace std; 

int main() {
	/*
	Table a(2);
	a.add("asdf", 3);
	a.add("qwerty", 4);
	cout << a.full() << endl;
	for (int i = 0; i < a.getCount(); i++) {
		cout << a[i].getName() << ' ' << a[i].getValue() << endl;
	}
	a.del("qwerty");
	a.del("asdf");
	cout << a.empty() << endl;
	Table b;
	b = a;
	b.add("dddddd", 2);
	b.add("kkkkkk", 6);
	for (int i = 0; i < b.getCount(); i++) {
		cout << b[i].getName() << ' ' << b[i].getValue() << endl;
	}
	Table c(a);
	c.add("ggggg", 1);
	c.add("hhhhh", 4);
	for (int i = 0; i < c.getCount(); i++) {
		cout << c[i].getName() << ' ' << c[i].getValue() << endl;
	}

	string a = "(3+4)-6+a^f-9*g";
	Poliz b(a);
	Poliz c;
	c = b;
	cout << b.GetStringPolis() << endl;
	cout << c.GetStringPolis() << endl;
	Table smeshoi = b.Getvariables();
	for (int i = 0; i < smeshoi.getCount(); i++) {
		cout << smeshoi[i].getName() << ' ' << smeshoi[i].getValue() << endl;
	}
	cout << endl;
	b.SetVar(3, 91);
	smeshoi = b.Getvariables();
	for (int i = 0; i < smeshoi.getCount(); i++) {
		cout << smeshoi[i].getName() << ' ' << smeshoi[i].getValue() << endl;
	}
	*/
	string a;
	cin >> a;
	Arithmetik b(a);
	Table table = b.getVariables();
	for (int i = 0; i < table.getCount(); i++) {
		string tmp = table[i].getName();
		if ((tmp[0] >= 'a' && tmp[0] <= 'z')||(tmp[0] >= 'A' && tmp[0] <= 'Z')) {
			cout << "Enter " << tmp << ":" << endl;
			double j;
			cin >> j;
			b.setVar(i, j);
		}
	}
	cout << b.calculate(); 
}


