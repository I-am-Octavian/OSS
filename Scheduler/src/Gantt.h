#pragma once

#include <iostream>
#include <vector>

#include "Scheduler.h"

void HelperFunc(int i, int arr[], char a)
{
    for (int j = 0; j < arr[i]; j++)
    {
        std::cout<<a<<a;
    }
}

void DashesInGanttChart(int size, int runtime[])
{
    for (int i = 0; i < size; i++)
    {
        if (i==0)
            std::cout<<"-";
        HelperFunc(i, runtime, '-');
        std::cout<<"---";
    }
    std::cout<<std::endl;
}

void GanttChart(int n, int runtime[], int process[])
{
    int time = 0;
    DashesInGanttChart(n,runtime);
    for (int i = 0; i < n; i++)
    {
        if (i==0)
            std::cout<<"|";
        HelperFunc(i, runtime, ' ');
        std::cout<<"P"<<process[i]<<"|";
    }
    std::cout<<std::endl;
    DashesInGanttChart(n,runtime);
    for (int i = 0; i < n; i++)
    {
        if (i==0)
            std::cout<<"0";
        HelperFunc(i, runtime, ' ');
        time = time + runtime[i];
        if (time<10)
            std::cout<<"  "<<time;
        else
            std::cout<<" "<<time;
    }
}

void DrawGantt(std::vector<Process>& theSchedule)
{
    int* runtime = (int*)alloca(theSchedule.size() * sizeof(int)); //{3, 6, 12, 9, 15};
    int* process = (int*)alloca(theSchedule.size() * sizeof(int));// {7,2,4,1,5}; //{"1","2","3","4","5"};
    for (int i = 0; i < theSchedule.size(); i++)
    {
        runtime[i] = theSchedule[i].burstTime;
        process[i] = theSchedule[i].pid;
    }
    GanttChart(theSchedule.size(), runtime, process);
}