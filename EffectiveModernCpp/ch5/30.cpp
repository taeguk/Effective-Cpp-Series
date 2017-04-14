#include <iostream>

struct test
{
	std::uint8_t a : 4,
				 b : 4;
};

template <typename T>
void foo(T& a) {}
template <typename T>
void bar(const T& a) {}

template <typename ...T>
void fwd_foo(T&&... args)
{
	foo(std::forward<T...>(args...));
}
template <typename ...T>
void fwd_bar(T&&... args)
{
	bar(std::forward<T...>(args...));
}

int main()
{
	struct test t = {};
	const struct test ct = {};

	// foo(t.b);  // Compile Error
	foo(ct.b);
	bar(t.b);
	bar(ct.b);

	// fwd_foo(t.b);  // Compile Error
	fwd_foo(ct.b);
	// fwd_bar(t.b);  // Compile Error
	fwd_bar(static_cast<std::uint8_t>(t.b));
	fwd_bar(ct.b);
}