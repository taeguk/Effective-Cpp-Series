#include <iostream>

class B;

class A {
public:
	unsigned int checksum;
private:
	B& b;
	A(B& b)
		:b(b), checksum(0x12341234)
	{}
public:
	static A& A::GetObject();
};

class B {
public:
	unsigned int checksum;
private:
	A& a;
	B(A& a)
		:a(a), checksum(a.checksum)
	{}
public:
	static B& GetObject() {
		static B b(A::GetObject());
		return b;
	}
};

A& A::GetObject() {
	static A a(B::GetObject());
	return a;
}

int main()
{	
	std::cout << "A : " << std::hex << A::GetObject().checksum << std::endl;
	std::cout << "B : " << std::hex << B::GetObject().checksum << std::endl;

	return 0;
}