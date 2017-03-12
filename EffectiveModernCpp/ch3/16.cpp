#include <iostream>
#include <mutex>
#include <atomic>

class Rect_Unsafe
{
public:
	void Set(std::int32_t width, std::int32_t height)
	{
		m_width = width;
		m_height = height;
	}

	std::int32_t Area() const
	{
		return m_width * m_height;
	}

private:
	std::int32_t m_width;
	std::int32_t m_height;
};

class Rect_Safe_1
{
public:
	void Set(std::int32_t width, std::int32_t height)
	{
		std::lock_guard<decltype(m_mutex)> lk(m_mutex);
		m_width = width;
		m_height = height;
	}

	std::int32_t Area() const
	{
		std::lock_guard<decltype(m_mutex)> lk(m_mutex);
		return m_width * m_height;
	}

private:
	mutable std::mutex m_mutex;
	std::int32_t m_width;
	std::int32_t m_height;
};

class Rect_Safe_2
{
public:
	bool CheckLockFree()
	{
		return m_items.is_lock_free();  // return true;
	}

	void Set(std::int32_t width, std::int32_t height)
	{
		struct Items items;
		items.width = width;
		items.height = height;
		m_items = items;
	}

	std::int32_t Area() const
	{
		struct Items items = m_items;
		return items.width * items.height;
	}

private:
	#pragma pack(push, 1)
	struct Items 
	{
		std::int32_t width;
		std::int32_t height;
	};
	#pragma pack(pop)

	std::atomic<struct Items> m_items;
};

class Example
{
	void Work()
	{
		std::lock_guard<decltype(m_mutex)> lk(m_mutex);
		// Do some work...
		m_status = 1;
		// Do some work...
		m_status = 2;
		// Do some work...
		m_status = 3;
	}

	int Status() const { return m_status; }

private:
	std::mutex m_mutex;
	std::atomic<int> m_status;  // "volatile int" is "incorrect".
};

int main()
{
	Rect_Safe_2 rect_safe_2;

	std::cout << (rect_safe_2.CheckLockFree() ? "Lock Free" : "Need Lock") << std::endl;  // Lock Free
	rect_safe_2.Set(12, 11);
	rect_safe_2.Area();
}