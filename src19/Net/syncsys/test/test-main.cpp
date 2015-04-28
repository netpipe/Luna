#include "../include/Sync_Network.h"
#include "../include/ThreadedObject.h"
#include "test-classes.h"
#include "performancetest.h"
#include <fstream>
#include <iostream>

#if defined(_DEBUG) && defined(_WIN32)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#ifndef _WIN32
#include <sched.h>
#include <ncursesw/ncurses.h>
#endif


int main(int argc, char* argv[])
{
#ifdef _CRTDBG_MAP_ALLOC
   _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

#ifndef _WIN32
    initscr();
#endif

	srand(helpers::PortableGetTime());

	//simple test
	//if(false)
	{
		TestServer server;
		TestClient client;
		TestObject object1(&server);
		helpers::NetworkBuffer buf;
		unsigned short msg;
		TestObject* obj1;
		TestServerClient* ptr;

		ptr = server.AddClient(&client, 1);
		object1.AddClient(ptr);

		ptr->PackData(buf, msg);
		_ASSERT(buf.GetWriteOffset() == 0);

		object1.Update(0);
		ptr->PackData(buf, msg);
		_ASSERT(buf.GetWriteOffset() != 0);

		obj1 = client.GetReceivedElement<TestObject>(1, false);
		_ASSERT(obj1 == 0);
		obj1 = client.GetReceivedElement<TestObject>(1, false, syncsys::NOTHING, 0, true);
		_ASSERT(obj1 != 0);

		obj1->Update(0);

		_ASSERT(obj1->blub1 == 0);
		_ASSERT(obj1->blub2 == 0);
		_ASSERT(obj1->blub3 == 0);
		_ASSERT(obj1->blub4 == 0);
		_ASSERT(obj1->blub5 == 0);

		client.UnPackData(buf, false);

		_ASSERT(obj1->blub1 == 0);
		_ASSERT(obj1->blub2 == 0);
		_ASSERT(obj1->blub3 == 0);
		_ASSERT(obj1->blub4 == 0);
		_ASSERT(obj1->blub5 == 0);

		object1.blub1	= 1;
		object1.blub2	= 'A';
		object1.blub3	= 3.0f;
		object1.blub4	= 4;
		object1.blub5	= false;

		object1.ManualRefresh(syncsys::UPDATE1);
		object1.Update(0);

		ptr->PackData(buf, msg);
		client.UnPackData(buf, true);

		_ASSERT(obj1->blub1 == 1);
		_ASSERT(obj1->blub2 == 'A');
		_ASSERT(obj1->blub3 == 3.0f);
		_ASSERT(obj1->blub4 == 4);
		_ASSERT(obj1->blub5 == false);

		delete obj1;
	}


	//scaling test
	unsigned clientcounts[] = {  500, 1000, 2000 }; //500, 1000, 2000
	unsigned threadcounts[] = { 0, 1, 2, 4 }; //0, 1, 2, 3, 4


	PerformanceTestSetup setup;
	setup.NetworkUpdateLimitInMs			= 20;
	setup.TimeToWasteInMs					= 80;
	setup.ClientChangeQuotaInPercent		= 0.00f;
	setup.ObjectChangeQuotaInPercent		= 0.05f;
	setup.ClientNeedObjectQuotaInPercent	= 0.50f;
	setup.RunOnlyLimitInMs					= 30 * 1000;
	setup.ClientsNewByTick					= 0;
	setup.ObjectsStartCount					= 0;
	setup.ObjectsNewByTick					= 100;

#ifdef _WIN32
	HANDLE hProcess = GetCurrentProcess();
	DWORD_PTR dwProcessAffinityMask, dwSystemAffinityMask;
	GetProcessAffinityMask(hProcess, &dwProcessAffinityMask, &dwSystemAffinityMask );
#else
    cpu_set_t set;
    sched_getaffinity(0, sizeof(set), &set);
    int dwProcessAffinityMask = CPU_COUNT(&set);
#endif

	std::ofstream file("ergebnisse.txt", std::ios::out | std::ios::trunc);

	file << setup;

	while(dwProcessAffinityMask)
	{
		for(unsigned c_counter = 0; c_counter < sizeof(clientcounts)/sizeof(unsigned); c_counter++)
		{
			for(unsigned t_counter = 0; t_counter < sizeof(threadcounts)/sizeof(unsigned); t_counter++)
			{
				setup.ThreadCount				= threadcounts[t_counter];
				setup.ClientsStartCount			= clientcounts[c_counter];
				PerformanceTest test(setup);
				unsigned starttime = helpers::PortableGetTime();
				test.run();
				unsigned time = helpers::PortableGetTime() - starttime;
				file << "Objectcount: " << test.GetObjectCount() <<"\tClientcount: "<< test.GetClientCount() << "\tNeeded time: "<< time << std::endl;
			}
		}

#ifdef _WIN32
		dwProcessAffinityMask = dwProcessAffinityMask >> 1;
		SetProcessAffinityMask(hProcess, dwProcessAffinityMask);
#else
        CPU_CLR(dwProcessAffinityMask - 1, &set);
        sched_setaffinity(0, sizeof(set), &set);
        dwProcessAffinityMask = CPU_COUNT(&set);
#endif
	}

	file << "\nfinished" << std::endl;
	file.close();

    #ifndef _WIN32
    endwin();
    #endif
	return 0;
}
