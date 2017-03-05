// 컴파일러는 비트수준 상수성만 보장해준다.
// 우리는 논리적 상수성을 고려해서 프로그래밍해야한다.
class Example {
private:
	int *data;
	int num;
	mutable int callCnt;
public:
	int* getData() const {
		// It is valid in bitwise constness, but invalid in logical constness.
		return data;	// compile ok.
	}
	int& getData(int idx) const {
		// It is valid in bitwise constness, but invalid in logical constness.
		return data[idx];	// compile ok.
	}
	int& getNum() const {
		// It is both invalid in bitwise constness and logical constness.
		return num;	// compile error.
	}
	void call() const {
		// It is invalid in bitwise constness, but valid in logical constness.
		++callCnt;	// compile ok.
	}
};

// enum, typedef, class의 유효범위는 선언된 scope내부, ﻿그리고 어디서나 선언될 수 있다.
// 단, template, namespace는 global혹은 namespace 안에서만 선언될 수 있다.

namespace TTTTT {
	class A {

	};
};

template<typename T>
class VV {
	T aa;
};
int main()
{
	template<typename T>
	class VVV {
		T aa;
	};

	namespace TTTT {
		class A {

		};
	};
	for (int i = 0; i < 10; ++i) {
		enum {AAA = 3};
		typedef int G;
		G a[AAA];

		class QQ {
			
		};
		QQ q;
		
		template<typename T>
		class VVVV {
			T aa;
		};
		

		VV<int> u;
		VVV<int> uu;
		VVVV<int> uuu;

		namespace TTT {
			class A {

			};
		};
	}
	QQ qq;
	G b[AAA];
}