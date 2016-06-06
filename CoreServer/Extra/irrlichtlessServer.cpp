#include <unistd.h>
#include <cstdio>
#include <string>

#ifdef WIN32
#include <windows.h>
#endif
#include <irrNet.h>
#include <iostream>

//#include "logging/logging.h"
#include "sqlCon.h"

using namespace irr;

//---------------- Squirrel Test--------------
        #include <stdarg.h>
        #include <stdio.h>

        #include <squirrel.h>
        #include <sqstdio.h>
        #include <sqstdaux.h>

        #ifdef SQUNICODE
        #define scvprintf vwprintf
        #else
        #define scvprintf vprintf
        #endif
        void printfunc(HSQUIRRELVM v, const SQChar *s, ...);
//---------------- Squirrel Test--------------

void handleConnection();
bool doit;
//	u32 address = netManager->getClientAddress(playerId);

class ServerNetCallback : public net::INetCallback
{
public:
	ServerNetCallback(net::INetManager* netManagerIn) : netManager(netManagerIn) {}

	// Override the "onConnect" function, don't forget to get the method
	// signature correct. Whenever a fresh client connects, their brand
	// spanking new player id will be passed to this function. A "u16"
	// is a typedef for an unsigned short, incase you were wondering.
	virtual void onConnect(const u16 playerId)
	{
        //!dont bother sending  anything on connect to the client its deaf --Unit
		//	net::SOutPacket packet;
		//	core::stringc message;
		//	message = "handshake";
			//message += playerId;
			//message += " has just connected.";
		//	packet << message;
		//	netManager->sendOutPacket(packet);
	}

	virtual void onDisconnect(const u16 playerId)
	{
	    doit=0;
		net::SOutPacket packet;
		core::stringc message;
		message = "Client number ";
		message += playerId;
		message += " has just left the building.";
		packet << message;
		netManager->sendOutPacket(packet);
	}

	virtual void handlePacket(net::SInPacket& packet)
	{
        core::stringc str;
		packet >> str;
            if (str == "handshake"){
                doit=true;
                std::cout << "AUTHORIZED with " << str.c_str();
            }
            if (str == "actPack2"){
                       //        doit=true;
                std::cout <<"Auth Communications 2" << str.c_str();
            }
		/*
    	core::stringc message;
		packet >> message;
		u16 playerId = packet.getPlayerId();


		if(message.size() > 20)
		{
			netManager->kickClient(playerId);
			u32 address = netManager->getClientAddress(playerId);
			banList.push_back(address);
			std::cout << "Player from " << address << " banned." << std::endl;
		}
		else
		{
			// Print the message.
			std::cout << "Client " << playerId << " said " << message.c_str() << std::endl;
		}
		*/
	}
private:
	core::array<u32> banList;
	net::INetManager* netManager;
};

int main()
{
//    log << std::string("Entering main loop");

		//  The default port that clients can connect to is set to 45000.
		net::INetManager* netManager = net::createIrrNetServer(0);
		ServerNetCallback* serverCallback = new ServerNetCallback(netManager);
		netManager->setNetCallback(serverCallback);
    //  netManager->setVerbose(true);


    handleConnection();

    sqlCon *sq =new sqlCon("ha.db");
    sq->execute("CREATE TABLE learnTb (a integer, b string);");


    while(1)
    {
		while(netManager->getConnectionStatus() != net::EICS_FAILED){
			netManager->update(100);break;} //update(delay);

        net::SOutPacket packet;// To send a packet, first you create an SOutPacket object.
        if (doit)
            {
                packet << "actPack2";
            }else{
                packet << "handshake"; // has to send something or it crashes the client
            }
        netManager->sendOutPacket(packet);
    }

        delete netManager;
		delete serverCallback;

    return 0;
}

//!----------------------------------------Squirrel Zone

void call_foo(HSQUIRRELVM v, int n,float f,const SQChar *s)
        {
              printfunc(v,"Calling Function %s" ,&s);
                int top = sq_gettop(v); //saves the stack size before the call
                sq_pushroottable(v); //pushes the global table
                sq_pushstring(v,_SC("foo"),-1);
                if(SQ_SUCCEEDED(sq_get(v,-2))) { //gets the field 'foo' from the global table
                        sq_pushroottable(v); //push the 'this' (in this case is the global table)
                        sq_pushinteger(v,n);
                        sq_pushfloat(v,f);
                        sq_pushstring(v,s,-1);
                        sq_call(v,4,0,0); //!calls the function last param is raise error
                        printfunc(v,"Function Called ", s);
                }
                sq_settop(v,top); //restores the original stack size
        }

void handleConnection()
{
                HSQUIRRELVM v;
                v = sq_open(1024); // creates a VM with initial stack size 1024
                printfunc(v,"running squirrel..\n");
                sqstd_seterrorhandlers(v);
                sq_setprintfunc(v, printfunc,printfunc); //sets the print function //0is errorfunction
                sq_pushroottable(v); //push the root table(were the globals of the script will be stored)

                if(SQ_SUCCEEDED(sqstd_dofile(v, _SC("test.nut"), 0, 1))) // also prints syntax errors if any
                {
                        call_foo(v,1,2.5,_SC("teststring"));
                }

                printfunc(v,"closing db \n");
                sq_pop(v,1); //pops the root table
                sq_close(v);
                exit(1);
}
int i = 43;
void printfunc(HSQUIRRELVM v, const SQChar *s, ...)
        {
                va_list arglist;
                va_start(arglist, s);
                fprintf(stderr, "its printing this -> %s %s %i\n",s , arglist,i);
                va_end(arglist);
        }

void handleAI()
{

}
