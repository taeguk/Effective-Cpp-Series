
//////////////////// no 36 //////////////////////

/*
class Base {
public:
virtual void bar() final {}
virtual void foo() {}
};
class Derived : public Base {
public:
//virtual void bar();  // compile error.
};
int main() {
Derived d;
Derived &obj = d;
obj.bar();
obj.foo();
}
*/

class Base {
public:
	virtual void bar() final {}
	virtual void foo() {}
};
class Derived : public Base {
public:
	//virtual void bar();  // compile error.
	void foo() override final {}
};
class Test : public Derived {

};
int main() {
	Derived d;
	Base &obj = d;
	obj.bar();
	obj.foo();
}