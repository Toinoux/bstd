/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** Stopable
*/

#pragma once

#include <future>
#include <chrono>

namespace bstd {
	class Stoppable {
	public:
		Stoppable() : _future(_exitSignal.get_future()) {};

		virtual void run() = 0;

		void operator()() {
			run();
		}

		bool stopRequested()
		{
			if (_future.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout)
				return false;
			return true;
		}

		void stop()
		{
			_exitSignal.set_value();
		}

	private:
		std::promise<void> _exitSignal;
		std::future<void> _future;
	};
}