
typedef int Data;

class Example {
public:
	const Data& getData() const { return data; }
	//Example() { data = 3; }
	//~Example() { data = 5; }
private:
	Data data;
};

int main() {
	
	const Data &data = Example().getData();
	// data is a dangling handle.
	//int a = data;
}