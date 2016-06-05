#include <iostream>
#include "../include/SyncSystem.h"
#include "../include/ThreadedObject.h"
#include "test-classes.h"
#include "performancetest.h"


#if defined_DEBUG && defined _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

TestObject::TestObject(syncsys::NetIDManager* e, const PerformanceTestSetup* setup)
	: NetEntity(e), Setup(setup), LastInsert(0), Run(true), blub1(0), blub2(0), blub3(0), blub4(0), blub5(0)
{
	memset(blub6, 0, sizeof(blub6));
}

TestObject::TestObject(syncsys::NetEntity* e, bool b)
	: NetEntity(e, b),  Setup(0), LastInsert(0), Run(true), blub1(0), blub2(0), blub3(0), blub4(0), blub5(0)
{
	memset(blub6, 0, sizeof(blub6));

}

TestObject::TestObject(syncsys::NetEntity* e, const PerformanceTestSetup& setup, bool ThreadObject)
	: NetEntity(e, true), Setup(&setup), LastInsert(0), Run(true), blub1(0), blub2(0), blub3(0), blub4(0), blub5(0)
{
	memset(blub6, 0, sizeof(blub6));

	if(ThreadObject)
	{
		WishedUpdateIntervalInMs = -1;
		StartThread();
	}
}

TestObject::TestObject(const syncsys::ContainerConnector& c, syncsys::SyncClient* cli, bool dodeserialize)
	: NetEntity(c, cli, dodeserialize), LastInsert(0),  Run(true), blub1(0), blub2(0), blub3(0), blub4(0), blub5(0)
{
	memset(blub6, 0, sizeof(blub6));
}

TestObject::~TestObject()
{
	Run = false;

	StopThread();

	for(std::list<TestObject*>::iterator it = SubObjects.begin(); it != SubObjects.end(); ++it)
		delete *it;
}

void TestObject::ThreadUpdate(unsigned time1)
{
	Update(time1);
	unsigned time2 = helpers::PortableGetTime();

	if(time2 - GetLastUpdateTimeInMs() < Setup->NetworkUpdateLimitInMs)
	{
		CreateSubObjects(Setup->ObjectsNewByTick);
		LastInsert = time2;
	}

	//then we waste some time
	while(Setup->TimeToWasteInMs > helpers::PortableGetTime() - time2)
	{
		int x=1, y=1;
		for(int counter = 0; counter < 100; counter++)
		{
			int z = x + y;
			x = y;
			y = z;
			z = x % y;
		}
	}
}

syncsys::NetActionFlag TestObject::ClientNeedsUpdates(syncsys::SyncServerClient* client)
{
//	return syncsys::ADDALL;
	return (GetNetID() == 1 || IsRunning() || rand() % 100 < Setup->ClientNeedObjectQuotaInPercent * 100 ? syncsys::ALL : syncsys::NOTHING);
}

void TestObject::Update(unsigned int acttime)
{
	syncsys::ChangedClientContainer out;
	PerformNeededUpdates(&out);

	if(IsServerElement() && GetNetID() != 1 && rand() % 100 < Setup->ObjectChangeQuotaInPercent * 100)
		FillObject();

	for(std::list<TestObject*>::iterator it = SubObjects.begin(); it != SubObjects.end(); ++it)
	{
		if(!Run)//boost the termination
			return;

		if((*it)->IsRunning())	(*it)->AddClients(out);
		else					(*it)->Update(acttime, out);
	}
}

void TestObject::CreateSubObjects(unsigned count)
{
	for(unsigned counter = 0; counter < count; counter++)
		SubObjects.push_back(new TestObject(this, *Setup));
}

void TestObject::FillObject(void)
{
	bool update = false;
	int rdm = rand();

	if(rdm % 2 == 0)	{ update = true; blub1++; }
	if(rdm % 3 == 0)	{ update = true; blub2++; }
	if(rdm % 5 == 0)	{ update = true; blub3++; }
	if(rdm % 7 == 0)	{ update = true; blub4++; }
	if(rdm % 11 == 0)	{ update = true; blub5++; }
	if(rdm % 17 == 0)	{ update = true; sprintf(blub6, "TestString %f, teststring %c, Teststring %f, StringTest %i", blub1, blub2, blub3, blub4); }

	if(update) ManualRefresh(syncsys::UPDATE1);
}


void TestObject::Serialize(syncsys::NetAction a, helpers::NetworkBuffer &buffer)
{
	switch(a)
	{
	case syncsys::INITDATA:
		{
//			buffer << number;
		}break;

	case syncsys::UPDATE1:
		{
			size_t size = sizeof(double) + sizeof(char) + sizeof(float) + sizeof(short) + sizeof(bool) + sizeof(int);
			buffer.CheckUnusedSize(size);

			buffer.Write(blub1);
			buffer.Write(blub2);
			buffer.Write(blub3);
			buffer.Write(blub4);
			buffer.Write(blub5);
			buffer.Write(blub6);
		}break;

    default:
		return;
	}
}

void TestObject::Deserialize(syncsys::NetAction a, helpers::NetworkBuffer &buffer)
{
	switch(a)
	{
	case syncsys::INITDATA:
		{
//			buffer >> number;
		}break;

	case syncsys::UPDATE1:
		{
			buffer.Read(blub1);
			buffer.Read(blub2);
			buffer.Read(blub3);
			buffer.Read(blub4);
			buffer.Read(blub5);
			buffer.Read(blub6, sizeof(blub6));
		}break;

    default:
		return;
	}
}

TestServerClient* TestServer::AddClient(TestClient* c, float ClientChangeQuotaInPercent)
{
	TestServerClient* ret = new TestServerClient(c, ClientChangeQuotaInPercent);
	clientlist.push_back(ret);
	return ret;
}

void TestServerClient::Update(bool updatedirectly)
{
	helpers::NetworkBuffer buf;
	unsigned short msg;
	if(Client && PackData(buf, msg))
		{}//Client->UnPackData(buf, updatedirectly);

	if(rand() % 100 < ClientChangeQuotaInPercent * 100)
		IncreaseVersion();
}

TestServer::TestServer()
{}

TestServer::~TestServer()
{
	ClearClientList();
}

void TestServer::RemoveClient(TestClient* c, bool onlysetpointer)
{
	for(std::list<TestServerClient*>::iterator it = clientlist.begin(); it != clientlist.end();)
		if(c == (*it)->Client)
		{
			if(onlysetpointer)
				(*it)->Client = NULL;
			else
			{
				(*it)->drop();
				it = clientlist.erase(it);
			}
			break;
		}
}

void TestServer::UpdateClients(bool updateclientobjectsdirectly)
{
	for(std::list<TestServerClient*>::iterator it = clientlist.begin(); it != clientlist.end();)
		if((*it)->IsKicked())
		{
			(*it)->drop();
			it = clientlist.erase(it);
		}
		else
		{
			(*it)->Update(updateclientobjectsdirectly);
			++it;
		}
}

void TestServer::ClearClientList(void)
{
	for(std::list<TestServerClient*>::iterator it = clientlist.begin(); it != clientlist.end(); ++it)
		(*it)->drop();

	clientlist.clear();
}
