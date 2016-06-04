
// 중첩 의존 이름은 기본적으로 타입이 아니라고 가정된다.
// 중첩 의존 이름이 타입임을 알려주기 위해서는 typename 키워드를 사용해야한다.
template <class T>
void example(void) {
	int a;  // 비의존 이름(non-dependent name)
	T b;  // 의존 이름(dependent name)
	auto c = T::variable;  // 중첩 의존 이름(nested dependent name)
	typename T::type d;  // 중첩 의존 타입 이름(nested dependent type name)
}

// typename은 중첩 의존 이름을 식별하는 데에만 사용할 수 있다.
template <class T>
void func(const T& obj);  // typename 쓰면 안 됨.

// 중첩 의존 이름이 '문맥상' 타입일 수 밖에 없는 경우에는 typename을 쓰면 안된다.
template <class T>
class Derived :public Base<T>::musttype {
	Derived(int val)
		: Base<T>::musttype(val)
	{}
};