#include <iostream>

class UnCopyable {
protected:
	UnCopyable() {}
	~UnCopyable() {}

private:
	UnCopyable(const UnCopyable&) {}
	UnCopyable& operator=(const UnCopyable&);
};

class Example : private UnCopyable {
};

Example make() {
	return Example();
}

class Test {
public:
	~Test() noexcept(false) {
		throw 3;
	}
};

int main()
{
	Example ex1;
	Test t;
	//Example ex2(ex1);	// compile error
	//ex2 = ex1;	// compile error
	//Example ex3(std::move(make()));	// compile error
	//ex1 = std::move(make());	// compile error

	return 0;
}
