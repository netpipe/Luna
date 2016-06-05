#include "../include/Sync_Network.h"
#include "../include/ThreadedObject.h"
#include "test-classes.h"
#include "performancetest.h"
#include <sstream>
//#include <fstream>
#include <iostream>
#include <iomanip>

#if defined(_DEBUG) && defined(_WIN32)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#ifndef _WIN32
#include <ncursesw/ncurses.h>
#endif

#undef max
#undef min

void PrintStream(std::stringstream &str)
{
    #ifdef _WIN32
	COORD pos = { 0, 2 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	std::cout << str.str().c_str();
	#else
    mvaddstr(0, 2, str.str().c_str());
    refresh();
    #endif
}

PerformanceTest::PerformanceTest(PerformanceTestSetup& setup)
	: running(false), LastInsert(0), root(&server, &Setup), Setup(setup)
{
	WishedUpdateIntervalInMs = setup.NetworkUpdateLimitInMs;
}

bool PerformanceTest::DoCreations(unsigned acttime)
{
	unsigned int objects = Setup.ObjectsNewByTick;
	unsigned int clients = Setup.ClientsNewByTick;

	if(LastInsert == 0)
	{
		objects = Setup.ObjectsStartCount;
		clients = Setup.ClientsStartCount;

		for(unsigned counter = 0; counter < clients; counter++)
		{
			TestClient* client = new TestClient();
			clientlist.push_back(client);
			root.AddClient(server.AddClient(client, Setup.ClientChangeQuotaInPercent));
		}

		for(unsigned counter = 0; counter < Setup.ThreadCount; counter++)
			root.SubObjects.push_back(new TestObject(&root, Setup, true));
	}
	else
		for(unsigned counter = 0; counter < clients; counter++)
		{
			TestClient* client = new TestClient();
			clientlist.push_back(client);
			root.AddClient(server.AddClient(client, Setup.ClientChangeQuotaInPercent));
		}

	if(!Setup.ThreadCount)
		root.CreateSubObjects(objects);

	LastInsert = acttime;
	return true;
}


void PerformanceTest::ThreadUpdate(unsigned time1)
{
	root.Update(time1);
	server.UpdateClients(true);

	unsigned time2			= helpers::PortableGetTime();
	unsigned NewestInsert	= LastInsert;
	unsigned LatestUpdate	= GetLastUpdateTimeInMs();
	unsigned LongestUpdate	= time2 - time1;

	if(Setup.ThreadCount)
	{
		for(std::list<TestObject*>::iterator it = root.SubObjects.begin(); it != root.SubObjects.end(); ++it)
		{
			LongestUpdate	= std::max((*it)->GetNeededUpdateTimeInMs(), LongestUpdate);
			LatestUpdate	= std::min((*it)->GetLastUpdateTimeInMs(), LatestUpdate);
			NewestInsert	= std::max((*it)->GetLastInsertTimeInMs(), NewestInsert);
		}
	}

	unsigned time3 = helpers::PortableGetTime();

	if(LongestUpdate <= Setup.NetworkUpdateLimitInMs && time3 - LatestUpdate <= Setup.NetworkUpdateLimitInMs)
		DoCreations(time3);
}

void PerformanceTest::run(void)
{
#ifdef _WIN32
	system("cls");
#else
    clear();
#endif
	running		= true;
	StartTime	= helpers::PortableGetTime();

	DoCreations(StartTime);
	StartThread();

	while(running)
	{
	    std::stringstream out;
		out << "Objectcount: " << server.GetObjectCount() <<"\tClientcount: "<< clientlist.size() << "\n\n\n";
		out << std::setw(15) << "\t" << std::setw(15) << "Neededtime" << std::setw(15) << "LastUpdate" << std::setw(15) << "LastInsert" << std::setw(15) << "ObjectCount\n";

		unsigned time1			= helpers::PortableGetTime();
		unsigned NewestInsert	= time1 - LastInsert;

		out << std::setw(15) << "Main" << std::setw(15) << time1 - GetLastUpdateTimeInMs();
		out << std::setw(15) << GetNeededUpdateTimeInMs() << std::setw(15) << NewestInsert << "\n";

		if(Setup.ThreadCount)
		{
			for(std::list<TestObject*>::iterator it = root.SubObjects.begin(); it != root.SubObjects.end(); ++it)
			{
				unsigned LastUpdate = (time1 > (*it)->GetLastUpdateTimeInMs() ? time1 - (*it)->GetLastUpdateTimeInMs() : 0);
				unsigned LastInsert = (time1 > (*it)->GetLastInsertTimeInMs() ? time1 - (*it)->GetLastInsertTimeInMs() : 0);

				out << std::setw(15) << "Thread" << std::setw(15) << (*it)->GetNeededUpdateTimeInMs();
				out << std::setw(15) << LastUpdate << std::setw(15) << LastInsert;
				out << std::setw(15) << (*it)->SubObjects.size() << "\n";

				NewestInsert = std::min(LastInsert, NewestInsert);
			}
		}

		out <<"\n\ntime: " << time1 << std::endl;

		bool timeout = Setup.TimeoutLimitInMs < time1 - StartTime;
		if(timeout || Setup.RunOnlyLimitInMs < NewestInsert)
		{
			out << "\n\n\n\n\n\nAbort test. Objectcount: " << server.GetObjectCount() <<"\tClientcount: "<< clientlist.size() << "\tReason: " << (timeout ? "Timeout" : "Limit reached") << std::endl;
			running = false;
		}
		PrintStream(out);
		helpers::PortableSleep(10);
	}

	StopThread();

	for(std::list<TestClient*>::iterator it = clientlist.begin(); it != clientlist.end(); ++it)
		delete *it;
}

std::ostream& operator << (std::ostream& off, const PerformanceTestSetup& t)
{
	off << std::left;
	off << std::setw(40) << "NetworkUpdateLimitInMs:" << t.NetworkUpdateLimitInMs << "\n";
	off << std::setw(40) << "TimeToWasteInMs:" << t.TimeToWasteInMs << "\n";
	off << std::setw(40) << "ObjectChangeQuotaInPercent:" << t.TimeToWasteInMs << "\n";
	off << std::setw(40) << "ClientChangeQuotaInPercent:" << t.TimeToWasteInMs << "\n";
	off << std::setw(40) << "ClientNeedObjectQuotaInPercent:" << t.TimeToWasteInMs << "\n";
	off << "\n" << std::endl;

	return off;
}
