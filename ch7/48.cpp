// https://gist.github.com/taeguk/5920b5773ae127dc51695cf1edd0f6c2
#include <iostream>

template <unsigned N>
struct IsPrime {
	static_assert(N >= 2, "The number must not be less than 2.");

	IsPrime() = delete;
	static bool value() { return static_cast<bool>(_value); }

private:
	template <unsigned D, bool, class Dummy = int>
	struct _CheckPrime {
		enum { value = _CheckPrime<D - 1, N % D == 0, Dummy>::value };
	};

	template <unsigned D, class Dummy>
	struct _CheckPrime<D, true, Dummy> {
		enum { value = 0 };
	};

	template <class Dummy>
	struct _CheckPrime<1, false, Dummy> {
		enum { value = 1 };
	};

	enum { _value = _CheckPrime<N - 1, false>::value };
};

template <unsigned _First, unsigned _Last, unsigned _Increment>
struct TestIsPrime {
	static_assert(_First <= _Last, "");
	static_assert(_Increment > 0, "");

	TestIsPrime() = delete;
	static void run() { 
		_TestIsPrimeLoop<_First, false>::run();
	}

private:
	template <unsigned _Cur, bool>
	struct _TestIsPrimeLoop {
		static void run() {
			std::cout << _Cur << (IsPrime<_Cur>::value() ? " is prime." : " is not prime.") << std::endl;
			_TestIsPrimeLoop<_Cur + _Increment, (_Cur + _Increment > _Last)>::run();
		}
	};

	template <unsigned _Cur>
	struct _TestIsPrimeLoop<_Cur, true> {
		static void run() {
		}
	};
};

int main() {
	TestIsPrime<2, 100, 1>::run();
}