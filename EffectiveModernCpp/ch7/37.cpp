#include <thread>
#include <condition_variable>
#include <iostream>
#include <atomic>
#include <vector>
#include <chrono>
#include <numeric>

class BackgroundWorkerPool
{
public:
	BackgroundWorkerPool()
	{
		std::cout << "[Main Thread] BackgroundWorkerPool() \n";
		m_worker[0] = std::thread(&BackgroundWorkerPool::BackgroundWorkerMain, this, 1);
		m_worker[1] = std::thread(&BackgroundWorkerPool::BackgroundWorkerMain, this, 2);
	}

	~BackgroundWorkerPool()
	{
		std::cout << "[Main Thread] ~BackgroundWorkerPool() \n";
		m_workerTerminated = true;
		m_cvData.notify_all();
		m_worker[0].join();
		m_worker[1].join();
		std::cout << "[Main Thread] After joining worker threads. \n";
	}

	void FeedData(const std::vector<int>& data)
	{
		{
			std::lock_guard<decltype(m_mutex)> lk(m_mutex);
			std::cout << "[Main Thread] Feed data. \n";
			m_data.insert(std::end(m_data), std::begin(data), std::end(data));
			m_dataExist = true;
		}
		m_cvData.notify_one();
	}

private:
	void BackgroundWorkerMain(int id)
	{
		while (true)
		{
			std::unique_lock<decltype(m_mutex)> lk(m_mutex);
			m_cvData.wait_for(lk, std::chrono::milliseconds(3000), [this]() {
				return m_dataExist || m_workerTerminated;
			});

			std::cout << "[Worker Thread " << id << "] Wake up! \n";

			if (m_workerTerminated)
				break;

			std::cout << "[Worker Thread " << id << "] WORK! \n";
			auto result = std::accumulate(std::begin(m_data), std::end(m_data), 0);
			std::cout << "[Worker Thread " << id << "] Result = " << result << " \n";
			m_data.clear();
			m_dataExist = false;
		}

		std::cout << "[Worker Thread " << id << "] I'm terminated. \n";
	}

	std::mutex m_mutex;
	std::atomic<bool> m_workerTerminated{ false };
	std::vector<int> m_data;
	bool m_dataExist{ false };
	std::condition_variable m_cvData;
	std::thread m_worker[2];
};

int main()
{
	BackgroundWorkerPool workerPool;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	workerPool.FeedData({ 1,2,3,4,5,6,7,8 });
	workerPool.FeedData({ 1 });
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	workerPool.FeedData({ 1,2,3,4,5 });
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	workerPool.FeedData({ 1,2 });
	workerPool.FeedData({ 1,2,3,4,5,6,7,8,9 });
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	workerPool.FeedData({ 1,2,3,4,5,6,7,8,9,10,11,12 });
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	/* Execution Result
		[Main Thread] BackgroundWorkerPool()
		[Main Thread] Feed data.
		[Main Thread] Feed data.
		[Worker Thread 2] Wake up!
		[Worker Thread 2] WORK!
		[Worker Thread 2] Result = 37
		[Main Thread] Feed data.
		[Worker Thread 2] Wake up!
		[Worker Thread 2] WORK!
		[Worker Thread 2] Result = 15
		[Main Thread] Feed data.
		[Main Thread] Feed data.
		[Worker Thread 1] Wake up!
		[Worker Thread 1] WORK!
		[Worker Thread 1] Result = 48
		[Main Thread] Feed data.
		[Worker Thread 1] Wake up!
		[Worker Thread 1] WORK!
		[Worker Thread 1] Result = 78
		[Main Thread] ~BackgroundWorkerPool()
		[Worker Thread 2] Wake up!
		[Worker Thread 2] I'm terminated.
		[Worker Thread 1] Wake up!
		[Worker Thread 1] I'm terminated.
		[Main Thread] After joining worker threads.
	*/
}