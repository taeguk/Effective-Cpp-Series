#include <initializer_list>

template <typename T>
void func_val(/*ParamType*/ T) {}

template <typename T>
void func_initlist(/*ParamType*/ std::initializer_list<T>) {}

int main()
{
	/***************** Exceptional Case in C++11 *****************/

	// func_val({ 1,2,3 });  // COMPILE ERROR!
	
	func_initlist({ 1,2,3 });  // T -> int
	                           // ParamType -> std::initializer_list<int>

	auto a = { 1,2,3 };  // auto -> std::initializer_list<int>
	                     // Type of Variable -> std::initializer_list<int>

	// std::initializer_list<auto> a = { 1,2,3 };  // There is no standard for it.

	/***************** Exceptional Case in C++14 *****************/

	auto lambda_func = [](auto) {};
	// lambda_func({ 1,2,3 });  // COMPILE ERROR!
}

auto exceptional_case_in_cpp14()
{
	// return { 1,2,3 };  // COMPILE ERROR!
}