#include "RoundRobin.h"

void RoundRobin::AddProcess(Process theProcess)
{
	std::lock_guard<std::mutex> lockExecutionQueue(m_MutexExecutionQueue);
	
	if (theProcess.burstTime == 0) throw;

	m_ExecutionQueue.emplace_back(theProcess);
}

void RoundRobin::Schedule()
{
	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(1000ms);

	if (m_ExecutionQueue.empty())
		return;

	std::lock_guard<std::mutex> lockExecutionQueue(m_MutexExecutionQueue);

	Process aProcess = m_ExecutionQueue.front();
	m_ExecutionQueue.pop_front();

	UpdateSchedule({ aProcess.pid, 1 });

	m_CurrentUsedTime++;
	aProcess.burstTime--;

	if (aProcess.burstTime == 0)
	{
		//m_ExecutionQueue.pop_front();
		m_CurrentUsedTime = 0;
	}
	else if (m_CurrentUsedTime >= m_MaxAllotedTime)
	{
		//m_ExecutionQueue.pop_front();
		m_ExecutionQueue.emplace_back(aProcess);
		m_CurrentUsedTime = 0;
	}
	else
	{
		//m_ExecutionQueue.pop_front();
		m_ExecutionQueue.emplace_front(aProcess);
	}
}

bool RoundRobin::isRunning()
{
	std::lock_guard<std::mutex> lockExecutionQueue(m_MutexExecutionQueue);
	return !m_ExecutionQueue.empty();
}
