// Function parameter pass by value involves copy initialization, not direct initialization.
class Example {
public:
	Example() {}
	explicit Example(const Example& ex) {}
	Example& operator=(const Example& ex) {}
};
void test(Example ex) {}
int main() {
	Example ex;
	test(Example());  // compile error! // means "Example test(Example)::ex = Example();"
	test(ex);         // compile error! // means "Example test(Example)::ex = main()::ex;"
	return 0;
}