class Example {
public:
	void doA() {}
	void doB() {}
	void doC() {}
	void doAll() {  // Bad!
		doA();
		doB();
		doC();
	}
};

void doAll(Example &ex) {  // Good!
	ex.doA();
	ex.doB();
	ex.doC();
}