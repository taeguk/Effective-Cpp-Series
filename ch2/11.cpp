#include <algorithm>

typedef int Data;

// Self assignment : Unsafe
// Exception : Unsafe
class Unsafe {
public:
	Data *pData;
	Unsafe& operator=(const Unsafe& obj) {
		delete pData;
		pData = new Data(*obj.pData);
		return *this;
	}
};

// Self assignment : Safe
// Exception : Unsafe
class Unsafe2 {
public:
	Data *pData;
	Unsafe2& operator=(const Unsafe2& obj) {
		if (this == &obj)
			return *this;
		delete pData;
		pData = new Data(*obj.pData);  // if exception occurs in new??
		return *this;
	}
};

// Self assignment : Safe
// Exception : Safe
class Safe {
public:
	Data *pData;
	Safe& operator=(const Safe& obj) {
		Data *pOrg = pData;
		pData = new Data(*obj.pData);
		delete pOrg;
		return *this;
	}
};

// Self assignment : Safe
// Exception : Unsafe
class Unsafe3 {
public:
	Data *pData, *pData2;
	Unsafe3& operator=(const Unsafe3& obj) {
		Data *pOrg = pData, *pOrg2 = pData2;
		pData = new Data(*obj.pData);
		pData2 = new Data(*obj.pData2);  // if exception occurs in this new??
		delete pOrg;
		delete pOrg2;
		return *this;
	}
};

// Using "copy and swap".
// Self assignment : Safe
// Exception : Safe
class RealSafe {
public:
	Data *pData, *pData2, data3;
	void swap(RealSafe &&obj) noexcept {
		std::swap(pData, obj.pData);
		std::swap(pData2, obj.pData2);
		data3 = std::move(obj.data3);
	}
	RealSafe& operator=(const RealSafe& obj) {
		RealSafe copy(obj);
		// std::swap(*this, copy);  // BAD!! Infinite loop occurs!
		swap(std::move(copy));
		return *this;
	}
};

int main() {
	RealSafe a, b, c;
	c.pData = new Data();
	c.pData2 = new Data();
	a = c = b = a = b = b = c = c = a = a = b = a = c;
	return 0;
}