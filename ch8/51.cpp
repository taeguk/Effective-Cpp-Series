#include <new>

class Example {
public:
	static void* operator new(std::size_t size) throw(std::bad_alloc) {

		if (size == 0) {  // 0 byte request.
			size = 1;
		}
		else if (size != sizeof(Example)) {  // new request of Derived Object.
			return ::operator new(size);
		}

		void *pMem = malloc(size);
		while (pMem == nullptr) {
			std::new_handler nh = std::set_new_handler(nullptr);
			std::set_new_handler(nh);

			if (nh) {
				nh();
			}
			else {
				throw std::bad_alloc();
			}

			pMem = malloc(size);
		}

		return pMem;
	}

	static void operator delete(void *pMem) noexcept {
		if (pMem == nullptr) {  // NULL pointer.
			return;
		}
		free(pMem);
	}
};

int main() {
	auto ptr = new Example();
	delete ptr;
}
