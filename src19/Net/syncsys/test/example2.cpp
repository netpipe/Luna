//this is a test of the syncsys+netlib part. You have to link winmm.lib, ws2_32.lib
//Visual Studio: use the "non DLL" runtime (project options->codegeneration)!
#include <iostream>
#include "../include/Sync_Network.h"

enum NetworkMessages { SYNCSYSDATA, ROOTNODEID, DOSOMETHINGSERVER };

class ExampleObject : public syncsys::NetEntity
{
	void Serialize(syncsys::NetAction a, helpers::NetworkBuffer &buffer)
	{
		if(a == syncsys::UPDATE1)
			buffer << changed;
	}
	void Deserialize(syncsys::NetAction a, helpers::NetworkBuffer &buffer)
	{
		if(a == syncsys::UPDATE1)
			buffer >> changed;
	}

public:
	bool changed;

	void ApplyChange(void)	{ changed = true; ManualRefresh(syncsys::UPDATE1); }

	ExampleObject(syncsys::NetIDManager* e)
		: syncsys::NetEntity(e), changed(false)
	{}
	ExampleObject(const syncsys::ContainerConnector& c, syncsys::SyncClient* cli)
		: syncsys::NetEntity(c, cli, true), changed(false)
	{}
};

class ExampleServerClient : public syncsys::MemExServerClient
{
	ExampleObject *object;
public:
	ExampleServerClient(netlib::InitData &info, ExampleObject *obj)
		: syncsys::MemExServerClient(info, SYNCSYSDATA), object(obj)
	{ 
		helpers::NetworkBuffer buffer;
		buffer << object->GetNetID();
		Send(buffer, ROOTNODEID);
		//this call is only needed for the root element.
		//Subelements gets the clientlist from their parent
		object->AddClient(this);
		std::cout << "sent the client the id of the root element for creation"<<std::endl;
	}

	bool AsyncCallbackFunc(netlib::Packet &p)
	{
		if(p.MSG == DOSOMETHINGSERVER)	object->ApplyChange();
		else							std::cout << "Should never happen. If it does please report it to me!" << std::endl;

		//true means that the packet should not be stored.
		//else it would be stored and handled in the next HandleSyncPacket call
		return true;
	}
};

class ExampleServer : public syncsys::MemExServer
{

	netlib::BasicServerClient* ClientConnected(netlib::InitData &info)
	{
		return new ExampleServerClient(info, WorldFirstObject);
	}

public:
	ExampleObject *WorldFirstObject;

	ExampleServer(void)	{ WorldFirstObject = new ExampleObject(this); }
	~ExampleServer()	{ delete WorldFirstObject; }
};

class ExampleClient : public syncsys::MemExClient
{
public:
	ExampleObject *CopiedObject;

	ExampleClient(void) : CopiedObject(NULL)	{}
	~ExampleClient()							{ delete CopiedObject; }

	void SyncCallbackFunc(netlib::Packet &p)
	{
		switch(p.MSG)
		{
		case SYNCSYSDATA:
			//second param tells that we want to update directly; use this only in a synchron case!
			//else update the objects frequently by calling PerformNeededUpdates on the object.
			UnPackData(p.Buffer, true);
			break;

		case ROOTNODEID:
			{
				unsigned id;
				p.Buffer >> id;
				//the last param tells it that it has to create the element even no data are recv for it
				//this can be dangerous but in this case its not harmful.
				CopiedObject = GetReceivedElement<ExampleObject>(id, syncsys::NOTHING, 0, true);
				std::cout << "created object." << std::endl;
			}break;

		default:
			std::cout << "Should never happen. If it does please report it to me!" << std::endl;
		}
	}
};

int main(int argc, char* argv[])
{
	char input;
	std::cout << "Hi, do you want to be server(s) or client(c)?\t";
	std::cin >> input;

	switch(input)
	{
	case 's':
		{
			ExampleServer server;

			//we let the server start its thread and listen to the given port
			if(!server.StartRunning(235368))
			{
				std::cout << "could not start the server listing at port 235368" << std::endl;
				return 0;
			}
			std::cout << "waiting for a client" << std::endl;

			while(!server.GetClientCount())
				helpers::PortableSleep(100);
			//because we just serve and reacts to the client
			//we wait until the client disconnects
			while(server.GetClientCount())
			{
				//update our object frequently to let it react to changes
				server.WorldFirstObject->Update();
				helpers::PortableSleep(100);
			}
			
			std::cout << "Client disconnected so going to finish exection"<<std::endl;
		}break;

	case 'c':
		{
			std::string address;
			ExampleClient client;

			//first we try to contact the server
			{
				std::cout << "server address? (default: localhost):\t" << std::endl;
				std::cin.get();//pop the \n from std::cin
				std::getline(std::cin, address);
				
				if(address.empty())	address = "localhost";
				//last parameter signals that we want to wait for the connect result
				if(!client.connectto(address.c_str(), 235368, true))
				{
					std::cout << "could not connect to the server using port 235367" << std::endl;
					return 0;
				}
			}
			//now we use the syncsys/netlib part 
			{
				helpers::NetworkBuffer buffer;
				buffer << "clientmessage; a int " << 235368;

				//lets wait for the answer
				while(!client.CopiedObject || !client.CopiedObject->changed)
				{
					//handle the queued packets
					client.HandleSyncPacket();
					if(client.CopiedObject)
						client.Send(0,0, DOSOMETHINGSERVER);
					helpers::PortableSleep(100);
				}
				//as you can see the client dont update its object frequently
				//reason: take a look at the UnPackData call in SyncCallbackFunc

				std::cout << "detected the object-change so going to finish exection"<<std::endl;
			}
		}break;

	default:
		return 0;
	}
	std::cin >> input;
	return 0;
}