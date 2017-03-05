#include <new>

// 항목33처럼 이름 가려짐 문제가 발생할 수 있다.
// 기본클래스 내부의 이름이 가려지는 건 using으로 해결할 수 있지만, 전역 이름의 가려짐은 해결할 수 없다.
// 따라서 전역 operator new/delete의 wrapper interface를 만듬으로서 해결한다.
// 좀 더 편하게 하려면 wrapper interface들을 가지는 클래스를 하나 만들고 이걸 상속함으로서 해결한다.
namespace name_hiding {
	namespace problem {
		class Example {
		public:
			using ::operator new;  // compile error. it is impossible :(
			static void* operator new(std::size_t size, void *pMem) noexcept {
				...
			}
		};
		void situation() {
			new Example();  // compile error.
		}
	}
	namespace solution {
		class GlobalNewDeleteFeature { ... };  // it has wrapper interfaces to global operator new/delete
		class Example : public GlobalNewDeleteFeature {
		public:
			using GlobalNewDeleteFeature::operator new;
			using GlobalNewDeleteFeature::operator delete;
			static void* operator new(std::size_t size, void *pMem) noexcept {
				...
			}
		};
		void situation() {
			new Example();  // compile ok.
		}
	}
}

// new 키워드로 객체를 생성할 때, 생성자에서 예외가 발생할 경우, operator delete가 호출되어야만 한다.
// 메모리할당시 사용된 operator new와 "추가 매개변수" 개수/타입이 똑같은 operator delete을 찾아서 호출한다.
// 만약, 그러한 operator delete가 존재하지 않는다면 아무것도 호출되지않고, memory leak이 발생하게 된다.
// 해결책은 항상 operator new와 operator delete는 짝이 맞게 정의하는 것이다.
// 추가적으로 new키워드와 delete키워드 또한 항상 짝이 맞게 사용해주어야한다. 그렇지 않을경우 문제가 생길 수 있다.
namespace memory_leak {
	class Example {
	public:
		Example() {
			throw 1;
		}
		static void* operator new(std::size_t size, void *pMem) noexcept {
			return ::operator new(size, pMem);
		}
	};
	void situation() {
		char buf[sizeof(Example)];
		auto ptr = new (buf) Example(); // operator delete is not called.
		delete ptr;  // call basic operator delete(="void ::operator delete(void*)").
	}
}

int main() {
}