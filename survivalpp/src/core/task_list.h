#pragma once

#include <future>
#include <queue>

class TaskList
{
public:
	void push(std::future<void>& task)
	{
		m_tasks.push(std::move(task));
	}

	void push(std::future<void>&& task)
	{
		m_tasks.push(std::move(task));
	}

	void wait()
	{
		while (!m_tasks.empty())
		{
			std::future<void>& task = m_tasks.front();
			task.wait();
			m_tasks.pop();
		}
	}

private:
	std::queue<std::future<void>> m_tasks;
};