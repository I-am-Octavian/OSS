#pragma once

#include "Scheduler.h"

class SJF : private Scheduler
{
public:
	void AddProcess(Process theProcess);
	void Schedule(); // Updates the execution queue every 1000ms
	bool isRunning();

private:
	std::priority_queue < Process, std::vector<Process>, Process> m_ExecutionQueue; // Current processes under execution
	// std::deque<Process> m_ExecutionQueue; 
	mutable std::mutex m_MutexExecutionQueue;
};

