#include <memory>
#include <functional>
#include <iostream>

int main()
{
	class Lambda
	{
		int& a;
		int b;
	public:
		Lambda(int &a, int b) : a(a), b(b) {}
		void operator()() const {
			a = 1;
			b = 2;  // Compiler Error
		}
	};

	int a, b;
	[&a, b]() {
		a = 1;
		b = 2;  // Compiler Error
	};
	Lambda lambda(a, b); lambda();

	////////////////////////////////////////////
	// Think "int &" is similar to "const int *".

	class MutableLambda
	{
		int & a;
		int b;
	public:
		MutableLambda(int &a, int b) : a(a), b(b) {}
		void operator()() {
			a = 1;
			b = 2;
		}
	};

	int a, b;
	[&a, b]() mutable {
		a = 1;
		b = 2;
	};
	MutableLambda mutableLambda(a, b); mutableLambda();
}