#include <utility>

template <typename T>
void func_ref(/*ParamType*/ T &) {}

template <typename T>
void func_ptr(/*ParamType*/ T *) {}

template <typename T>
void func_unv_ref(/*ParamType*/ T &&) {}

template <typename T>
void func_val(/*ParamType*/ T) {}

template <typename T, std::size_t N>
void func_arr_ref(/*ParamType*/ T (&)[N]) {}

int main()
{
	/**********************************************/
	const volatile int a = 3;

	func_ref(a);  // T -> const volatile int
	              // ParamType -> const volatile int &

	func_ptr(&a);  // T -> const volatile int
	               // ParamType -> const volatile int *

	func_unv_ref(a);  // T -> const volatile int &
			          // ParamType -> const volatile int &

	func_unv_ref(std::move(a));  // T -> const volatile int
			                     // ParamType -> const volatile int &&

	func_val(a);  // T -> int
	              // ParamType -> int

	/**********************************************/
	const char * const str = "hello";

	func_ref(str);  // T -> const char * const
	                // ParamType -> const char * const &

	func_ptr(str);  // T -> const char
	                // ParamType -> const char *

	func_val(str);  // T -> const char *
	                // ParamType -> const char *

	/**********************************************/
	const int arr[10] = {};

	func_ref(arr);  // T -> const int [10]
	                // ParamType -> const int (&)[10]
	                // *** An array doesn't decay ***

	func_ptr(arr);  // T -> const int
					// ParamType -> const int *
	                // An array decays to pointer.

	func_val(arr);  // T -> const int *
	                // ParamType -> const int *

	func_arr_ref(arr);  // T -> const int
	                    // ParamType -> const int (&)[10]

	/**********************************************/
	void junk();

	func_ref(junk);   // T -> void ()
	                  // ParamType -> void (&)()
					  // *** A function doesn't decay ***

	//func_ref(&junk); // COMPILE ERROR!!
	                   // The reason is that a function doesn't decay in this case.

	func_ptr(junk);   // T -> void ()
					  // ParamType -> void (*)()
	                  // A function decays to a pointer.

	func_ptr(&junk);  // Same to above.

	func_val(&junk);  // T -> void (*)()
	                  // ParamType -> void (*)()
}

void junk() {}