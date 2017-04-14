#include <iostream>

class Example
{
public:
	Example() = default;
	Example(const Example &) { std::cout << "copy constructor" << std::endl; }
	Example(Example &&) { std::cout << "move constructor" << std::endl; }
	Example(const Example &&) { std::cout << "const move constructor" << std::endl; }
};

/* std::forward is meaningful only for universal reference in template. */

void test1(Example ex)
{
	std::cout << "Test 1" << std::endl;
	Example a(std::forward<Example>(ex));	// move constructor
	Example b(std::forward<Example&>(ex));	// copy constructor
	Example c(std::forward<Example&&>(ex));	// move constructor
}

void test2(Example& ex)
{
	std::cout << "Test 2" << std::endl;
	Example a(std::forward<Example>(ex));	// move constructor
	Example b(std::forward<Example&>(ex));	// copy constructor
	Example c(std::forward<Example&&>(ex));	// move constructor
}

void test3(Example&& ex)
{
	std::cout << "Test 3" << std::endl;
	Example a(std::forward<Example>(ex));	// move constructor
	Example b(std::forward<Example&>(ex));	// copy constructor
	Example c(std::forward<Example&&>(ex));	// move constructor
}

template <typename T>
void test4(T&& a) /* universal reference(=forwarding reference) */
{
	std::cout << "Test 4" << std::endl;
	Example aa(std::forward<T>(a));
}

template <typename T>
void test5(const T&& a) /* Cannot be universal reference */
{
	std::cout << "Test 5" << std::endl;
	Example aa(std::forward<T>(a));  // Compile Error 
									 // because cannot remove "const" through static_cast in std::forward.

	// Compile OK.
	// Example aa(std::forward<T>(const_cast<T>(a)));
}

int main()
{
	test1(Example());
	test2(Example());
	test3(Example());

	test4(Example());
	// test5(Example());

	const Example ex;
	test4(std::move(ex));   // const move constructor
	Example(std::move(ex));	// const move constructor
}