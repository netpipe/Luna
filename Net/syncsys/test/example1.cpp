//this is a test of the netlib part. You have to link winmm.lib, ws2_32.lib
//Visual Studio: use the "non DLL" runtime (project options->codegeneration)!

#include <iostream>
#include "../include/Sync_Network.h"

enum NetworkMessages { TEXTMESSAGE, SYNCSYSDATA };

class ExampleServerClient : public syncsys::MemExServerClient
{
public:
	ExampleServerClient(netlib::InitData &info) : syncsys::MemExServerClient(info, SYNCSYSDATA)	{}

	bool AsyncCallbackFunc(netlib::Packet &p)
	{
		switch(p.MSG)
		{
		case TEXTMESSAGE:
			{
				std::string	str1;
				int			i;

				p.Buffer >> str1 >> i;
				std::cout << "\n" << str1 << i << "\n" << std::endl;
			}break;

		default:
			std::cout << "Should never happen. If it does please report it to me!" << std::endl;
		}
		//true means that the packet should not the stored.
		//else it would be stored and handled in the next HandleSyncPacket call
		return true;
	}
};

class ExampleServer : public syncsys::MemExServer
{
	netlib::BasicServerClient* ClientConnected(netlib::InitData &info)
	{
		return new ExampleServerClient(info); 
	}
};

class ExampleClient : public syncsys::MemExClient
{
public:
	bool finished;

	ExampleClient(void) : finished(false)		{}

	bool AsyncCallbackFunc(netlib::Packet &p)
	{
		switch(p.MSG)
		{
		case TEXTMESSAGE:
			{
				std::string	str1, str2;
				float		f;
				bool		b;

				p.Buffer >> str1 >> f >> str2 >> b;
				std::cout << "\n" << str1 << f << str2 << b << "\n" << std::endl;
				finished = true;
			}break;

		default:
			std::cout << "Should never happen. If it does please report it to me!" << std::endl;
		}
		//true means that the packet should not be stored.
		//else it would be stored and handled in the next HandleSyncPacket call
		return true;
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
			if(!server.StartRunning(235367))
			{
				std::cout << "could not start the server listing at port 235367" << std::endl;
				return 0;
			}
			std::cout << "waiting for a client" << std::endl;

			while(!server.GetClientCount())
				helpers::PortableSleep(100);
			//now we use the netlib part
			{
				helpers::NetworkBuffer buffer;
				buffer << "servermessage; a float " << 34.0f << " a boolean " << true;

				//the second parameter is for categorisating the message; see HandlePacket methods
				server.Send(buffer, TEXTMESSAGE);
			}
			std::cout << "sent textmessage to the client" << std::endl;
			//we wait until the client disconnects
			while(server.GetClientCount())
				helpers::PortableSleep(100);
			
			std::cout << "Client disconnected => going to finish exection"<<std::endl;
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
				if(!client.connectto(address.c_str(), 235367, true))
				{
					std::cout << "could not connect to the server using port 235367" << std::endl;
					return 0;
				}
			}
			//now we use the netlib part
			{
				helpers::NetworkBuffer buffer;
				buffer << "clientmessage; a int " << 235367;

				//the second parameter is for categorisating the message; see HandlePacket methods
				client.Send(buffer, TEXTMESSAGE);
				std::cout << "sent textmessage to the server" << std::endl;
				//lets wait for the answer
				while(!client.finished)
					helpers::PortableSleep(100);

				std::cout << "received a message => going to finish exection"<<std::endl;
			}	
		}break;

	default:
		return 0;
	}
	std::cin >> input;
	return 0;
}