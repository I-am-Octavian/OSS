#include "RoundRobin.h"
#include "SJF.h"

int main()
{
	std::atomic<bool> clientRunning = true;
	SJF server;
	std::thread client([&] {
		
		/****** Add Processes Here ******/
		server.AddProcess({ 1, 6 });
		server.AddProcess({ 2, 8 });
		server.AddProcess({ 3, 7 });
		server.AddProcess({ 4, 3 });
		/*******************************/

		clientRunning = false;
		});

	while (clientRunning || server.isRunning())
	{
		try 
		{
			server.Schedule();
		}
		catch (std::exception e)
		{
			continue;
		}
	}

	client.join();
}
