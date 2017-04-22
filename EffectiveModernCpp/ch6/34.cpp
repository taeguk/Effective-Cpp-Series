/*
	https://godbolt.org/g/25uYMS
*/

#include <vector>
#include <functional>

class Functor {
private:
	int a;
	int b;
public:
	Functor(int a, int b) : a(a), b(b) {}
	bool operator()(int n) const { return a < n && n < b; }
};

bool comp(int a, int b, int n) { return a < n && n < b; }

bool test_bind_function_pointer(int a, int b, int c)
{
	auto bind_func = std::bind(comp, a, b, std::placeholders::_1);
	std::vector<decltype(bind_func)> vec;
	vec.emplace_back(bind_func);
	return vec.back()(c);
}

bool test_bind_functor(int a, int b, int c)
{
	auto bind_func = std::bind(Functor(a, b), std::placeholders::_1);
	std::vector<decltype(bind_func)> vec;
	vec.emplace_back(bind_func);
	return vec.back()(c);
}

bool test_functor(int a, int b, int c)
{
	std::vector<Functor> vec;
	vec.emplace_back(a, b);
	return vec.back()(c);
}

bool test_lambda(int a, int b, int c)
{
	auto lambda = [a, b](int n) { return a < n && n < b; };
	std::vector<decltype(lambda)> vec;
	vec.emplace_back(lambda);
	return vec.back()(c);
}

int main() 
{
	test_bind_function_pointer(1, 2, 3);
	test_bind_functor(1, 2, 3);
	test_functor(1, 2, 3);
	test_lambda(1, 2, 3);
}