#include <iostream>
#include <memory>

class Example
{
public:
	Example(int, int)
	{ std::cout << "Example(int, int) called!" << std::endl;}

	/* http://stackoverflow.com/questions/17803475/why-is-stdinitializer-list-often-passed-by-value */
	Example(std::initializer_list<int>)
	{ std::cout << "Example(std::initializer_list<int>) called!" << std::endl;}
};

int main()
{
	auto a = std::make_shared<Example>(1, 2); /* Example(int, int) called! */
	auto b = std::make_shared<Example>(std::initializer_list<int>{1, 2}); /* Example(std::initializer_list<int>) called! */
	auto tmp = { 1, 2 };
	auto c = std::make_shared<Example>(tmp); /* Example(std::initializer_list<int>) called! */

	/* https://akrzemi1.wordpress.com/2016/07/07/the-cost-of-stdinitializer_list/ */
	int arr[4] = { 1,3,5,7 };
	auto qq = { arr[0],2,arr[1],4,arr[2],6,arr[3],8 };
	std::cout << sizeof(qq) << std::endl; // 8 in x86, 16 in x64
}