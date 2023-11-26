#include "Scheduler.h"

void Scheduler::UpdateSchedule(Process theProcess)
{
    std::lock_guard<std::mutex> lockSchedule(m_MutexSchedule);
    if (m_Schedule.empty() || m_Schedule.back() != theProcess.pid)
    {
        m_Schedule.push_back(theProcess.pid);
        std::cout << theProcess.pid << " --> ";
    }
    std::cout << "#";

}