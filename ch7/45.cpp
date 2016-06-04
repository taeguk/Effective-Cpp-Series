
template <class T>
class SmartPointer {
public:
	template<class U>
	explicit SmartPointer(U *ptr)
		: ptr(ptr)
	{}

	SmartPointer(const SmartPointer &other);
	template <class U>
	SmartPointer(const SmartPointer<U>& other)
		: ptr(other.get())
	{}
	T* get() const { return ptr; }
private:
	T* ptr;
};

class Base {};
class Derived : public Base{};
class Base2 {};

int main() {
	SmartPointer<Base> a(new Derived);  // compile ok.
	SmartPointer<Base2> b(new Base);  // compile error.
	SmartPointer<Derived> c(new Derived);  // compile ok.
	SmartPointer<Base> d = c;  // compile ok.
}