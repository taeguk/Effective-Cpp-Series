#include <set>
#include <iostream>

class Example
{
public:
	explicit Example(int a, int b)
		: m_a(a), m_b(b)
	{
		std::cout << "Example(int, int) called. \n";
	}
	~Example()
	{
		std::cout << "~Example() called. \n";
	}
	Example(const Example& other)
		: m_a(other.m_a), m_b(other.m_b)
	{
		std::cout << "Example(const Example&) called. \n";
	}
	Example(Example&& other)
		: m_a(other.m_a), m_b(other.m_b)
	{
		std::cout << "Example(Example&&) called. \n";
	}
	Example& operator=(const Example& other)
	{
		std::cout << "operator=(const Example&) called. \n";
		m_a = other.m_a;
		m_b = other.m_b;
		return *this;
	}
	Example& operator=(Example&& other)
	{
		std::cout << "operator=(Example&&) called. \n";
		m_a = other.m_a;
		m_b = other.m_b;
		return *this;
	}

	bool operator<(const Example& other) const { return m_a + m_b < other.m_a + m_b; }

private:
	int m_a, m_b;
};

int main()
{
	std::set<Example> s;
	Example ex(11, 22);
	s.insert(ex);

	Example ex1(33, 44), ex2(55, 66);
	std::cout << "\n";
	std::cout << "-- insert when not duplicated --\n";
	s.insert(ex1);
	std::cout << "--------------------------------\n\n";
	std::cout << "-- emplace when not duplicated --\n";
	s.emplace(ex2);
	std::cout << "---------------------------------\n\n";

	std::cout << "-- insert when duplicated --\n";
	s.insert(ex);
	std::cout << "----------------------------\n\n";
	std::cout << "-- emplace when duplicated --\n";
	s.emplace(ex);
	std::cout << "-----------------------------\n\n";

	/* Execution Result
		Example(int, int) called.
		Example(const Example&) called.
		Example(int, int) called.
		Example(int, int) called.

		-- insert when not duplicated --
		Example(const Example&) called.
		--------------------------------

		-- emplace when not duplicated --
		Example(const Example&) called.
		---------------------------------

		-- insert when duplicated --
		----------------------------

		-- emplace when duplicated --
		Example(const Example&) called.
		~Example() called.
		-----------------------------

		~Example() called.
		~Example() called.
		~Example() called.
		~Example() called.
		~Example() called.
		~Example() called.
	*/
}