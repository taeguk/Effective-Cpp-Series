// int func_1();
decltype(auto) func_1() { int a = 1; return a; }

// int& func_2();
decltype(auto) func_2() { int a = 1; return (a); }

template <typename T>
class Example
{
public:
	Example(const T& param) : m_var(param) {}
private:
	T m_var;
};

int main()
{
	/* Usage of "decltype" */

	auto var_1 = func_1();

	decltype(var_1) var_2;

	//Example ex(var_2);  // COMPILE ERROR!
	                      // Maybe it is possible since C++17.
	Example<decltype(var_2)> ex(var_2);
}