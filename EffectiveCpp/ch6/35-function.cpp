#include <functional>

class Base {};
class Derived :public Base {};

Derived dd(Derived) { return Derived(); }
Derived db(Base) { return Derived(); }
Base bd(Derived) { return Base(); }
Base bb(Base) { return Base(); }

int main() {
	std::function<Base(Derived)> f = db;
	f(Derived());
}