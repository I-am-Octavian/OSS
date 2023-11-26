#include "SJF.h"

void SJF::AddProcess(Process theProcess)
{
	std::lock_guard<std::mutex> lockExecutionQueue(m_MutexExecutionQueue);

	if (theProcess.burstTime == 0) throw;

	m_ExecutionQueue.emplace(theProcess);
}

void SJF::Schedule()
{
	using namespace std::literals::chrono_literals;

	if (m_ExecutionQueue.empty())
	{
		std::this_thread::sleep_for(10ms);
		return;
	}

	Process aProcess;
	{
		std::lock_guard<std::mutex> lockExecutionQueue(m_MutexExecutionQueue);

		aProcess = m_ExecutionQueue.top();
		m_ExecutionQueue.pop();
	}

	UpdateSchedule(aProcess);

	std::this_thread::sleep_for(std::chrono::milliseconds(aProcess.burstTime * 1000));

}

bool SJF::isRunning()
{
	std::lock_guard<std::mutex> lockExecutionQueue(m_MutexExecutionQueue);
	return !m_ExecutionQueue.empty();
}
