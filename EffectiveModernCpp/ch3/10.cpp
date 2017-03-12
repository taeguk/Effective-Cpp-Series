#include <type_traits>

enum class Enum_A { A_1, A_2, A_3, };  // SCOPED, and implicit type conversion is not admitted.
namespace Enum_B { enum { B_1, B_2, B_3, }; }  // SCOPED, and implicit type conversion to underlying type.

int main()
{
	int arr[] = { 1,2,3,4 };

	// arr[Enum_A::A_1];  // COMPILER ERROR!
	arr[static_cast<std::underlying_type_t<Enum_A>>(Enum_A::A_1)];

	arr[Enum_B::B_1];
}