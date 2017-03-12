#include <array>
#include <iostream>

class Example
{
public:
	constexpr Example(int num)
		: m_num(num)
	{}

	constexpr int Num() const noexcept { return m_num; }
	//constexpr Example& operator+=(const Example& ex) noexcept { m_num += ex.m_num; return *this; } // Not compiled in VS2015. But it is okay in C++14.
	//constexpr void SetNum(int num) noexcept { m_num = num; } // Not compiled in VS2015. But it is okay in C++14.

private:
	int m_num;
};

int main()
{
	constexpr Example a(3), b(5);
	//a += b;
	std::array<int, a.Num()> arr;
	std::cout << arr.size();
}