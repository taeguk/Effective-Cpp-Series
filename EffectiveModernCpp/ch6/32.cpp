#include <memory>
#include <functional>
#include <iostream>

class Example {};

int main()
{
	std::unique_ptr<Example> p;

	auto func_in_cpp_11 = std::bind(
		[](const std::unique_ptr<Example>& p) {
			std::cout << "I'm an example in C++11 :(" << std::endl;
		},
		std::move(p)
	);

	auto func_in_cpp_14 = [p = std::move(p)]() {
		std::cout << "I'm an example in C++14 :)" << std::endl;
	};

	func_in_cpp_11();
	func_in_cpp_14();
}