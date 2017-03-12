#include <iostream>
#include <string>

using namespace std;

class Example
{
public:
	Example(int a, int b) { cout << "normal" << endl; }
	Example(std::initializer_list<string> i) { cout << "initializer_list" << endl; }
};

int main()
{
	Example ex1({ 1, 2 }); // print "normal" (THERE IS NO "COMPILE ERROR")
	Example ex2{ 1, 2 };  // print "normal"
}