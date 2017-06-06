


PyObject * Python::PyIrr_Connect(PyObject * self,PyObject * args){

	return Py_BuildValue("");
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
	PyArg_ParseTuple(args,"ll",&t,&x);
	//	clientid
//	netManager->sendOutPacket(powerPacket);

//		 Print a simple menu.
//		std::cout 	<< "Example 1. What would you like to do?" << std::endl
//				<< "1. Change the cannon rotation." << std::endl
//				<< "2. Change the cannon power." << std::endl
//				<< "3. Send a message." << std::endl;

//		char i = 0;
//		std::cin >> i;
//t=1;
//
//		switch(t)
//		{
//			case '1':
//			{
////				 Here we create a rotation packet and send it to the server.
//				net::SOutPacket rotationPacket;
//				rotationPacket << (c8)EPT_ROTATION; // Remember to cast to the correct type.
//
////				 Ask for the rotation.
//				f32 rotation;
//				//std::cout << "Please enter a rotation: ";
//				//std::cin >> rotation;
//				rotationPacket << x;//rotation;
//				netManager->sendOutPacket(rotationPacket);
//				break;
//			}
//			case '2':
//			{
////				 And here we create a power packet and send it to the server.
//				net::SOutPacket powerPacket;
//				powerPacket << (c8)EPT_POWER; // Remember to cast to the correct type.
////				 Ask for the power.
//				f32 power;
//				std::cout << "Please enter the power: ";
//				std::cin >> power;
//				powerPacket << power;
//				netManager->sendOutPacket(powerPacket);
//				break;
//			}
//			case '3':
//			{
////				 We'll also send the server a message in the form of a string.
//				net::SOutPacket messagePacket;
//				messagePacket << (c8)EPT_MESSAGE; // Remember to cast to the correct type.
////				 Ask for the message.
//				char message[512] = {};
//				std::cout << "Please enter a message:" << std::endl;
//				std::cin >> message;
//				messagePacket << message;
//				netManager->sendOutPacket(messagePacket);
//				break;
//			}
//			default:
//				break;
//		}


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
//
	return Py_BuildValue("");
}

PyObject * Python::PyIrr_restartServer(PyObject * self,PyObject * args){

	return Py_BuildValue("");
}


PyObject * Python::PyIrr_Update(PyObject * self,PyObject * args){

		// Here is the update loop, we will exit if there is a connection problem.
	//	while(netManager->getConnectionStatus() != net::EICS_FAILED)
	//	{
			// Here we update.
	//		netManager->update(1000);
	//	}


	return Py_BuildValue("");
}

