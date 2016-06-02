
class Example {
public:
	explicit Example(int n) {}
};

typedef int Data;

int main() {
	Example ex(1);

	Example(3);

	(Example) 3;

	// 规过 1
	// 积己磊 1锅 + 家戈磊 1锅 + 措涝 n锅
	for (Data data, int i = 0; i < n; ++i) {
		data = func(i);
	}
	// 规过 2
	// 积己磊 n锅 + 家戈磊 n锅
	for (int i = 0; i < n; ++i) {
		Data data = func(i);
	}
	// 规过 1 if cost(措涝) > cost(积己磊 + 家戈磊),
	// 规过 2 otherwise.
}