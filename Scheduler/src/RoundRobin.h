#pragma once

#include "Scheduler.h"

class RoundRobin : private Scheduler
{
public:
	RoundRobin(uint32_t theMaxAllotedTime) : m_MaxAllotedTime(theMaxAllotedTime), m_CurrentUsedTime(0) {}
	void AddProcess(Process theProcess);
	void Schedule(); // Updates the execution queue every 1000ms
	bool isRunning() override;
	inline std::vector<Process>& GetSchedule() 
	{
		std::lock_guard<std::mutex> lock(m_MutexSchedule);
		return m_Schedule; 
	}


private:
	//std::vector<uint32_t> m_Schedule; // The order of execution of processes
	//mutable std::mutex m_MutexSchedule;

	const uint32_t m_MaxAllotedTime;
	uint32_t m_CurrentUsedTime;

	std::deque<Process> m_ExecutionQueue; // Current processes under execution
	mutable std::mutex m_MutexExecutionQueue;
};

