#include <algorithm>

namespace ExampleStuff {
	template <typename T>
	class ExampleImpl {
	};

	template <typename T>
	class Example {
	public:
		void swap(Example &ex) {
			using std::swap;
			swap(pImpl, ex.pImpl);
		}
	private:
		ExampleImpl<T> *pImpl;
	};

	template <typename T>
	void swap(Example<T> a, Example<T> b) {
		a.swap(b);
	}
}

template <typename T>
void func(T& a, T& b) {
	using std::swap;
	swap(a, b);
}

int main() {
	ExampleStuff::Example<int> a, b;
	func(a, b);
}