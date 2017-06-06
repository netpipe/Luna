
//bool works;
////bool login=0;
////net::SOutPacket rotationPacket;
//	//vector3df tmpvect;
//    bool connected,doit,login=0;
//
enum E_PACKET_TYPE
{
	EPT_ROTATION = 1,
	EPT_POWER = 2,
	EPT_MESSAGE = 3
};


//class ClientNetCallback : public net::INetCallback
//{
//public:
//
//	 //	u16 playerId = packet.getPlayerId();
//	virtual void handlePacket(net::SInPacket& packet)
//	{
//		//packet.decryptPacket("hushthisissecret");
//		//packet.deCompressPacket();
//		core::stringc str;
//		packet >> str;
//
//		core::vector3df vec;
//		packet >> vec;
//
//        //	f32 height;
//        //	packet >> height;
//        //	rotationPacket << str;
//
//        if (!login){
//            if (str == "handshake"){
//			login=1;
//            std::cout << "Authorized" << str.c_str() << std::endl;
//            }
//        }
//       // }else{}
////        resetV=true;
//        // m_cVehicle2->resetVehicle();//( core::vector3df(vec[0],vec[1],vec[2]));
//        tmpvect=vector3df(vec);
//        std::cout << "vehicle   coords xyz=" << vec.X << vec.Y << vec.Z << std::endl;
//        //login=false;
//	}
//};









 //The client callback.
//class ClientNetCallback : public net::INetCallback
//{
//public:
//	// Our handlePacket function.
//	virtual void handlePacket(net::SInPacket& packet)
//	{
//		// Just like the server, we obtain the packet id and print
//		// the information based on the packet we received. I hope the
//		// rest of this function is self-explanatory.
//		c8 packetid;
//		packet >> packetid;
//
//		switch((E_PACKET_TYPE)packetid)
//		{
//		case EPT_ROTATION:
//			f32 cannonAngle;
//			packet >> cannonAngle;
//			std::cout << "Server says that the cannon angle is now " << cannonAngle << std::endl;
//			break;
//		case EPT_POWER:
//			f32 cannonPower;
//			packet >> cannonPower;
//			std::cout << "Server says that the cannon power is now " << cannonPower << std::endl;
//			break;
//		default:
//			// We don't care about any other types, so we catch them here and break.
//			break;
//		}
//	}
//};

//	// Ask the user whether they want to be the server or a client.
//	std::cout << "Client (c) or Server (s)?";
//	char i;
//	std::cin >> i;
//
//	{
//		// Create a client and pass in the client callback.
//		// You may want to change the ip address to a remote one and experiment
//		// with connecting to a remote host.
//		ClientNetCallback* clientCallback = new ClientNetCallback();
//		net::INetManager* netManager = net::createIrrNetClient(clientCallback, "127.0.0.1");


//		// Clean up.
//		delete netManager;
//		delete clientCallback;
//	}
//
//	// And we're done, return 0 and make like a banana.
//	return 0;
//}
