
template <class T>
class Base {
public:
	void func_of_base() {}
};

// C++은 '이른 진단(early diagnose)'을 선호한다.
// 무효성 체크를 '클래스 템플릿 정의의 구문 분석' 시에 진행한다. (인스턴화될 때가 아니라)
// 그래서 클래스 템플릿이 어디로 부터 상속되는 지 구체적으로 모른다.
// 따라서 func_of_base가 들어있는지도 알 수 없다. 그것이 문제다.
// 컴파일러에 따라 표준을 어기고, 이를 허용해주는 경우도 있다. (visual studio 2013이 그러네요ㅜ)
template <class T>
class Problem :public Base<T> {
public:
	void foo() {
		func_of_base();  // compile error!
	}
};

// this pointer를 이용한 해결책.
template <class T>
class SolutionOne :public Base<T> {
public:
	void foo() {
		this->func_of_base();  // 함수가 상속되는 것으로 가정된다.
	}
};

// using 선언을 이용한 해결책.
template <class T>
class SolutionTwo :public Base<T> {
public:
	using Base<T>::func_of_base;  // Base<T>에 함수가 있는 것으로 가정된다.
	void foo() {
		func_of_base();
	}
};

// 명시적호출을 통한 해결책.
// 단, 가상 함수 바인딩이 무시되므로 안쓰는게 좋다.
template <class T>
class SolutionThree :public Base<T> {
public:
	void foo() {
		Base<T>::func_of_base();  // 명시적으로 함수를 한정한다.
	}
};

// 개인적인 생각으로는 해결책1(this pointer를 이용한 해결책) 이 가장 좋아보인다.


int main() {
}