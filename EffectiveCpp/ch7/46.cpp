#include <xutility>
std::input_iterator_tag a;
// 템플릿 인자 추론 과정에서는 암시적 타입 변환이 고려되지 않습니다.
// 암시적 타입 변환을 고려하려면 타입을 명확히 알아야하는데 추론작업중임으로 당연히 불가능한 것입니다 ㅎㅎ
namespace issue {
	template <class T>
	class Example {
	public:
		Example(int num)
		{}
	};

	template <class T>
	const Example<T> operator*(const Example<T> &lhs, const Example<T> &rhs) {
		return Example<T>();
	}

	void situation() {
		Example<int> a(2);
		a * 2;  // compile error.
	}
}

// 해결책은 비멤버 함수를 클래스 템플릿안에 담는 것입니다.
// 그러면 클래스 템플릿이 인스턴스화될 때 비멤버 함수도 같이 정의되므로 문제가 없습니다.
// 비멤버 함수를 클래스 템플릿 안에 담기위해 friend 선언을 사용합니다.
namespace solution {
	template <class T>
	class Example {
	public:
		Example(int num)
		{}

		friend const Example<T> operator*(const Example<T> &lhs, const Example<T> &rhs) {
			return Example<T>(2);
		}
	};

	void situation() {
		Example<int> a(2);
		a * 2;  // compile ok!
	}
}

int main() {
	
}