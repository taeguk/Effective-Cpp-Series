#include <iostream>
#include <string>

class Bad
{
public:
	~Bad()
	{
		throw 1;
	}
};

const std::string str[] = {
	"depth 1", "depth 2", "depth 3"
};

template <typename int Index>
class Test {
public:
	~Test() {
		std::cout << str[Index] << std::endl;
	}
};
void f3() {
	Test<2> t;
	throw 111;
}
void f2() {
	Test<1> t;
	f3();
}
void f1() {
	Test<0> t;
	f2();
}

int main()
{
	try {
		f1();
	}
	catch(...) {
		std::cout << "catch!" << std::endl;
	}
	try {
		//Bad bad;	// ok.
		//Bad bads[2]; // not ok.
	}
	catch (...) {

	}
	/*
	try
	{
		Bad   bad;
	}
	catch (...)
	{
		std::cout << "Print This" << std::endl;
	}

	try
	{
		Bad   bad;
		throw 2;
	}
	catch (...)
	{
		std::cout << "Never print this " << std::endl;
	}
	*/
}