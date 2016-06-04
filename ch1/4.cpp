#include <string>
#include <iostream>

using namespace std;

class test
{
public:
	test(const char *name)
		: _name(name)
	{
		cout << _name << " created" << endl;
	}

	~test()
	{
		cout << _name << " destroyed" << endl;
	}

	string _name;
	static test t; // static member
};
test test::t("static in class");

test t("global variable");

void f()
{
	static  test t("static variable");
	static int num = 10; // POD type, init before enter main function

	test t2("Local variable");
	cout << "Function executed" << endl;
}

int main()
{
	test t("local to main");
	cout << "Program start" << endl;
	f();
	cout << "Program end" << endl;
	return 0;
}