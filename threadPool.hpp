/*
** EPITECH PROJECT, 2018
** tech2
** File description:
** ThreadPool
*/

#pragma once

#include <condition_variable>
#include <type_traits>
#include <functional>
#include <utility>
#include <vector>
#include <thread>
#include <future>
#include <atomic>
#include <mutex>
#include <queue>

namespace bstd {
	using Task = std::function<void ()>;
	class ThreadPool {
	public:
		explicit ThreadPool(size_t NbThread) : _RunningThread(0), _Active(true)
		{
			_Threads.reserve(NbThread);
			for (size_t i = 0; i <  NbThread; ++i) {
				_Threads.emplace_back([this]{
					while (true) {
						Task task;
						{
							std::unique_lock<std::mutex> lock(_QueueLock);
							_QueueCondition.wait(lock, [this]{
								return (!_Active || !_Tasks.empty());
							});
							if (!_Active && _Tasks.empty())
								return;
							task = std::move(_Tasks.front());
							_Tasks.pop();
						}
						task();
					}
				});
			}
		};

	public:
		template<typename Function, typename ... Arguments>
		auto addTask(Function &&f, Arguments &&... args)
			-> std::future<typename std::result_of<Function(Arguments ...)>::type>
		{
			using result_of = typename std::result_of<Function(Arguments ...)>::type;

			auto call = std::bind(std::forward<Function>(f), std::forward<Arguments>(args)...);
			auto task = std::make_shared<std::packaged_task<result_of()>>(call);
			std::future<result_of> taskFuture = task->get_future();
			{
				std::lock_guard<std::mutex> lock(_QueueLock);
				_Tasks.emplace([task]{
					(*task)();
				});
			}
			_QueueCondition.notify_one();
			return (taskFuture);
		}

	public:
		bool isRunning() const noexcept {
			return _Active;
		};

	public:
		~ThreadPool() {
			_Active = false;
			_QueueCondition.notify_all();
			for (auto &Worker : _Threads)
				Worker.join();
		};

	private:
		std::vector<std::thread> _Threads;
		std::queue<Task> _Tasks;

	private:
		std::mutex _QueueLock;
		std::condition_variable _QueueCondition;

	private:
		std::atomic<size_t> _RunningThread;
		std::atomic<bool> _Active;
	};
}
