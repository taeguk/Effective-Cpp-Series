#include <new>

// RAII방식으로 new handler을 관리하는 클래스
class NewHandlerRAII {
public:
	explicit NewHandlerRAII(std::new_handler nh) noexcept {
		old = std::set_new_handler(nh);
	}
	~NewHandlerRAII() noexcept {
		std::set_new_handler(old);
	}
	NewHandlerRAII(const NewHandlerRAII&) = delete;
	NewHandlerRAII& operator=(const NewHandlerRAII&) = delete;
private:
	std::new_handler old;
};

// class별로 new handler를 지정할 수 있는 기능과 인터페이스를 담고 있는 클래스 템플릿.
template <class T>
class NewHandlerFeature {
public:
	static std::new_handler set_new_handler(std::new_handler nh) noexcept {
		auto old = currentHandler;
		currentHandler = nh;
		return old;
	}
	static void* operator new(std::size_t size) throw(std::bad_alloc) {
		NewHandlerRAII nhr(currentHandler);
		return ::operator new(size);
	}
	static void* operator new(std::size_t size, void *pMem) noexcept {
		// NewHandlerRAII nhr(currentHandler);
		return ::operator new(size, pMem);
	}
	static void* operator new(std::size_t size, const std::nothrow_t& nt) noexcept {
		NewHandlerRAII nhr(currentHandler);
		return ::operator new(size, nt);
	}
	// operator new[]는 생략..
private:
	static std::new_handler currentHandler;
};
template <class T>
std::new_handler NewHandlerFeature<T>::currentHandler = nullptr;

// 신기하게 반복되는 템플릿 패턴 (CRTP : Curiously Recurring Template Pattern)
// also called to "나만의 것(Do It For Me)" by Scott Meyers.
// CRTP패턴을 사용함으로써 기본 클래스의 정적변수를 파생 클래스별로 각자 소유할 수 있게된다.
class Example : public NewHandlerFeature<Example> {
public:
	Example() {}
	~Example() {}
private:
	char dummy[8];
};

void func() {}

int main() {
	Example::set_new_handler(func);
	auto ptr1 = new Example();
	char buf[sizeof(Example)];
	auto ptr2 = new (buf) Example();
	auto ptr3 = new (std::nothrow) Example();
}