
PyMethodDef irr_Network[] =
{
    {"connect",Python::PyIrr_Connect,METH_VARARGS,"connect"},
    {"disconnect",Python::PyIrr_Disconnect,METH_VARARGS,"disconnect"},
    {"ping",Python::PyIrr_Ping,METH_VARARGS,"ping"},
    {"sendFile",Python::PyIrr_sendFile,METH_VARARGS,"sendFile"},
    {"send",Python::PyIrr_Send,METH_VARARGS,"sendFile"},
    {"update",Python::PyIrr_Update,METH_VARARGS,"sendFile"},

    {"encrypt",Python::PyIrr_Encrypt,METH_VARARGS,"encrypt"},
    {"decrypt",Python::PyIrr_Decrypt,METH_VARARGS,"addSphereNode"},
    {"server",Python::PyIrr_Server,METH_VARARGS,"startServer"},
    {"restartServer",Python::PyIrr_restartServer,METH_VARARGS,"restartServer"},

	{NULL,NULL,0,NULL}
};


PyObject * Python::PyIrr_Connect(PyObject * self,PyObject * args){
class ClientNetCallback : public net::INetCallback
{
public:
	// Our handlePacket function.
	virtual void handlePacket(net::SInPacket& packet)
	{
		packet.decryptPacket("hushthisissecret");

		// irrNetLite compression is even easier! The ZLib library is used
		// here, just call compressPacket/decompressPacket to
		// compress/decompress a packet. Again, do not try to decompress
		// an un-compressed packet or read from a compressed packet without
		// decompressing it! Another thing to keep in mind is that you should
		// decompress and decrypt in the correct order. If you compressed a file
		// and then encrypted it when it was sent, you must decrypt it first
		// before trying to decompress it, same goes for the other order.
		packet.deCompressPacket();

		core::stringc str;
		packet >> str;

		core::vector3df vec;
		packet >> vec;

		f32 height;
		packet >> height;

		std::cout << "Message: " << str.c_str();
		std::cout << " Position: " << vec.X << " " << vec.Y << " " << vec.Z;
		std::cout << " Height: " << height << " ft";
		std::cout << std::endl;
	}
};
//	enum E_PACKET_TYPE
//{
//	EPT_ROTATION = 1,
//	EPT_POWER = 2,
//	EPT_MESSAGE = 3
//};
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

		ClientNetCallback* clientCallback = new ClientNetCallback();
	//	net::INetManager* netManager = net::createIrrNetClient(clientCallback, "127.0.0.1");
	//	net::INetManager* netManager = net::createIrrNetServer(clientCallback);

		net::INetManager* netManager = net::createIrrNetClient(0, "127.0.0.1");
		netManager->setVerbose(true); // debug messages
	return Py_BuildValue("l",netManager);
}

PyObject * Python::PyIrr_Disconnect(PyObject * self,PyObject * args){

	return Py_BuildValue("");
}

PyObject * Python::PyIrr_Ping(PyObject * self,PyObject * args){

	return Py_BuildValue("");
}

PyObject * Python::PyIrr_sendFile(PyObject * self,PyObject * args){

	return Py_BuildValue("");
}

PyObject * Python::PyIrr_Send(PyObject * self,PyObject * args){
	int x,t;
	long netMan;
	char *message2;
	PyArg_ParseTuple(args,"ls",&netMan,&message2);
	net::INetManager* netManager=netMan;


			net::SOutPacket packet;

			// Then you can use the streaming operator << to add new data to it.
			packet << "Help I am stuck on a mountain!";

			// You can even chain the << operators like so, just like with ostream.
			packet << core::vector3df(50.0f, 30.0f, 20.0f) << 50.0f;

			// Compress the packet, not much to be said.
			packet.compressPacket();

			// Encrypt the packet. Note that here we are just using a simple key
			// that is shared among the client and the server. In more sophisticated
			// implementations you may want to generate a random key on the server for
			// each client and send that using a shared key, then use the new key for
			// further communication. Remember that the key should be 16 characters
			// long, and obviously the client and server must share the same key.
			packet.encryptPacket("hushthisissecret");

			// A simple call to "sendOutPacket" will send the packet to the server.
			netManager->sendOutPacket(packet);


	return Py_BuildValue("");
}

PyObject * Python::PyIrr_Receive(PyObject * self,PyObject * args){

	return Py_BuildValue("");
}

PyObject * Python::PyIrr_Encrypt(PyObject * self,PyObject * args){

	return Py_BuildValue("");
}

PyObject * Python::PyIrr_Decrypt(PyObject * self,PyObject * args){

	return Py_BuildValue("");
}

PyObject * Python::PyIrr_Server(PyObject * self,PyObject * args){
// on off restart
// change host / port
class MyNetCallback : public net::INetCallback
{
public:
	// Our handlePacket function.
	virtual void handlePacket(net::SInPacket& packet)
	{
		packet.decryptPacket("hushthisissecret");

		// irrNetLite compression is even easier! The ZLib library is used
		// here, just call compressPacket/decompressPacket to
		// compress/decompress a packet. Again, do not try to decompress
		// an un-compressed packet or read from a compressed packet without
		// decompressing it! Another thing to keep in mind is that you should
		// decompress and decrypt in the correct order. If you compressed a file
		// and then encrypted it when it was sent, you must decrypt it first
		// before trying to decompress it, same goes for the other order.
		packet.deCompressPacket();

		core::stringc str;
		packet >> str;

		core::vector3df vec;
		packet >> vec;

		f32 height;
		packet >> height;

		std::cout << "Message: " << str.c_str();
		std::cout << " Position: " << vec.X << " " << vec.Y << " " << vec.Z;
		std::cout << " Height: " << height << " ft";
		std::cout << std::endl;
	}
};
		MyNetCallback* netCallback = new MyNetCallback();
		net::INetManager* netManager = net::createIrrNetServer(netCallback);

	return Py_BuildValue("l",netManager);
}

PyObject * Python::PyIrr_restartServer(PyObject * self,PyObject * args){

	return Py_BuildValue("");
}


PyObject * Python::PyIrr_Update(PyObject * self,PyObject * args){

	long netMan;
	PyArg_ParseTuple(args,"l",&netMan);
	net::INetManager* netManager=netMan;

		// Here is the update loop, we will exit if there is a connection problem.
	   if (netManager->getConnectionStatus() != net::EICS_FAILED)
		{
			// Here we update.
			netManager->update(0);
		}
	//	delete netManager;
	//	delete clientCallback;

	return Py_BuildValue("");
}

