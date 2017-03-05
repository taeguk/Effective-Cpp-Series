#include <memory>
typedef int Data;

// 핸들 클래스 기법에 대한 예제
namespace HandleClassExample {

	// 실제 구현에 대한 내용을 가지고 있는 클래스
	// ExampleImpl은 유저에게 완전히 숨겨진다.
	class ExampleImpl {
	public:
		ExampleImpl(const Data &data)
			:data(data)
		{}
		Data getData() const { return data; }
	private:
		Data data;
	};

	// ExampleImpl에 대한 핸들 역할을 하는 클래스.
	// 유저에겐 Example의 선언 혹은 정의만 제공된다.
	class Example {
	public:
		Example(const Data &data)
			:pImpl(std::make_shared<ExampleImpl>(data))
		{}
		Data getData() const { return pImpl->getData(); }
	private:
		std::shared_ptr<ExampleImpl> pImpl;
	};
}

// 인터페이스 클래스 기법에 대한 예제
namespace InterfaceClassExample {

	// ExampleImpl에 대한 인터페이스 역할을 하는 클래스.
	// 유저에겐 Example의 선언 혹은 정의만 제공된다.
	class Example {
	public:
		virtual ~Example() = default;
		virtual Data getData() const = 0;
		static std::shared_ptr<Example> create(const Data &data) {
			return std::make_shared<ExampleImpl>(data);
		}
	};

	// 실제 구현에 대한 내용을 가지고 있는 클래스
	// ExampleImpl은 유저에게 완전히 숨겨진다.
	class ExampleImpl : public Example {
	public:
		ExampleImpl(const Data &data)
			:data(data)
		{}
		Data getData() const { return data; }
	private:
		Data data;
	};
}