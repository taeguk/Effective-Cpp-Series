#include <memory>
#include <iostream>

class Example {};

void deletor_func(Example *ptr) { delete ptr; }

struct DeletorClass {
	void operator() (Example *ptr) const { delete ptr; }
};

struct DeletorClass2 {
	DeletorClass2(std::int32_t num)
	{
		m_arr[0] = m_arr[1] = num;
	}
	void operator() (Example *ptr) const { delete ptr; }
	std::int32_t m_arr[2];
};

int main()
{
	auto a = std::make_unique<Example>();

	auto deletor = [](Example *ptr) { delete ptr; };
	auto b = std::unique_ptr<Example, decltype(deletor)>(new Example, deletor);
	/* In C++17,
		auto b = std::unique_ptr(new Example, [](Example *ptr) { delete ptr; });
	*/

	int num = 13;
	auto deletor2 = [num](Example *ptr) { delete ptr; };
	auto c = std::unique_ptr<Example, decltype(deletor2)>(new Example, deletor2);

	auto d = std::unique_ptr<Example, void(*)(Example *)>(new Example, [](Example *ptr) { delete ptr; });
	auto e = std::unique_ptr<Example, DeletorClass>(new Example, DeletorClass());
	auto f = std::unique_ptr<Example, DeletorClass2>(new Example, DeletorClass2(1));

	// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Empty_Base_Optimization
	// Result in x86 : 4 4 8 8 4 12
	std::cout << sizeof(a) << " " << sizeof(b) << " " << sizeof(c) << " " << 
		sizeof(d) << " " << sizeof(e) << " " << sizeof(f) << std::endl;
}