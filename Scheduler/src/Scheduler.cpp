#include "Scheduler.h"

void Scheduler::UpdateSchedule(Process theProcess)
{
    std::lock_guard<std::mutex> lockSchedule(m_MutexSchedule);
    if (m_Schedule.empty() || m_Schedule.back().pid != theProcess.pid)
    {
        m_Schedule.emplace_back(theProcess);
        std::cout << theProcess.pid << " --> ";
    }
    else if (m_Schedule.back().pid == theProcess.pid)
    {
        m_Schedule.back().burstTime += theProcess.burstTime;
    }
    std::cout << "#\n";

}