
// 파생된 클래스에서 가상함수를 재정의하지 않을 경우,
// 의도하지 않은 동작이 발생할 여지가 있다.
namespace issue {
	class Base {
	public:
		virtual void func() { /* default working */ }
	};
	class Derived : public Base {
		// no declaration of func.
	};
	void situation() {
		Derived obj;
		obj.func();  // no error.
	}
}
// 해결책 1
// 순수가상함수로 선언을 하고, default함수를 비가상함수로 제공하는 방법.
namespace solution_1 {
	class Base {
	public:
		virtual void func() = 0;
	protected:
		void defaultFunc() { /* default working */ }
	};
	class Derived : public Base {
	public:
		// must declare func.
		virtual void func() { defaultFunc(); }
	};
	void situation() {
		Derived obj;
		obj.func();
	}
}
// 해결책 2
// 순수가상함수로 선언을 하고 정의를 제공해버린다(?). ㅋㅋㅋ
// default 함수를 또 선언해야하는 점이 거슬릴 경우 이용할 수 있는 방법.
namespace solution_2 {
	class Base {
	public:
		virtual void func() = 0;
	};
	class Derived : public Base {
	public:
		// must declare func.
		virtual void func() { Base::func(); }
	};
	void situation() {
		Derived obj;
		obj.func();
	}
	void Base::func() { /* default working */ }
}
