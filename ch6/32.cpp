
namespace using_declaration {
	class Base {
	public:
		void f() {}
		void f(int x) {}
	};

	class Derived : public Base {
	public:
		using Base::f;  // this statement must be public.
		void f(int x, int y) {}
	};
}

namespace forwarding_function {
	class Base {
	public:
		void f() {}
		void f(int x) {}
	};

	class Derived : private Base {
	public:
		void f() {
			Base::f();
		}
		void f(int x, int y) {}
	};
}

int main() {
	using_declaration::Derived obj;
	obj.f();
	obj.f(1);
	obj.f(1, 2);
	forwarding_function::Derived obj2; 
	obj2.f();
	obj2.f(1);  // compile error.
	obj2.f(1, 2);
}