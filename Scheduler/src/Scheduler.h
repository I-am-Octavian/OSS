#pragma once

#include <vector>

#include <queue>
#include <deque>
#include <atomic>
#include <mutex>
#include <chrono>
#include <thread>
#include <iostream>

struct Process
{
	uint32_t pid;
	uint32_t burstTime;

	// Returns false of theFirst has lesser burst time than theSecond
	bool operator()(Process theFirst, Process theSecond)
	{
		return theFirst.burstTime > theSecond.burstTime;
	}
};

class Scheduler
{
public:
	virtual void AddProcess(Process theProcess) = 0;
	
	// This funciton Implements scheduling
	virtual void Schedule() = 0;
	virtual bool isRunning() = 0;

	void UpdateSchedule(Process theProcess);
	
	
	inline std::vector<uint32_t>& GetSchedule()
	{
		std::lock_guard<std::mutex> lockSchedule(m_MutexSchedule);
		return m_Schedule;
	}

	std::vector<uint32_t> m_Schedule; // The order of execution of processes
	mutable std::mutex m_MutexSchedule;
};

